/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2017
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
 * \file      pmlib_clk_rate_data_tda2px.c
 *
 * \brief     PMLIB Clock Rate Data Base used by Clock Rate Manager.
 *
 * \note      This file is auto generated from the Clock Rate xlsm.
 *            DO NOT Modify Manually.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/hw_types.h>
#include "pmhal_vm.h"
#include "pmhal_mm.h"
#include "pmhal_cm.h"
#include "pmhal_clocktree.h"
#include "pmlib_clk_rate_data_priv.h"
#include "pmhal_prcm.h"

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

/* -------------------------------------------------------------------------- */
/*                     DPLL Configuration Structures                          */
/* -------------------------------------------------------------------------- */

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_ABE
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_ABE_200_9_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_ABE, M = 200, N = 9
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_ABE_200_9_M2_1 =
{200U, 9U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_ABE_200_9_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_ABE
 *         PMHAL_PRCM_DPLL_POST_DIV_M2X2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2X2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_ABE, M = 200, N = 9
 *         PMHAL_PRCM_DPLL_POST_DIV_M2X2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1 =
{200U, 9U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H12 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H12_4 =
{PMHAL_PRCM_DPLL_POST_DIV_H12, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H12 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H12_4 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H12_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H24 = 6
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H24_6 =
{PMHAL_PRCM_DPLL_POST_DIV_H24, 6U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H24 = 6
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H24_6 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H24_6, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H14 = 5
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H14_5 =
{PMHAL_PRCM_DPLL_POST_DIV_H14, 5U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H14 = 5
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H14_5 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H14_5, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H14 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H14_4 =
{PMHAL_PRCM_DPLL_POST_DIV_H14, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H14 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H14_4 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H14_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H22 = 5
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H22_5 =
{PMHAL_PRCM_DPLL_POST_DIV_H22, 5U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H22 = 5
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H22_5 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H22_5, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H13 = 62
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H13_62 =
{PMHAL_PRCM_DPLL_POST_DIV_H13, 62U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H13 = 62
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H13_62 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H13_62, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H23 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H23_4 =
{PMHAL_PRCM_DPLL_POST_DIV_H23, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H23 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H23_4 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H23_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H21 = 6
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H21_6 =
{PMHAL_PRCM_DPLL_POST_DIV_H21, 6U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H21 = 6
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H21_6 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H21_6, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H21 = 5
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H21_5 =
{PMHAL_PRCM_DPLL_POST_DIV_H21, 5U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H21 = 5
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H21_5 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H21_5, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_CORE
 *         PMHAL_PRCM_DPLL_POST_DIV_H21 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H21_4 =
{PMHAL_PRCM_DPLL_POST_DIV_H21, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_CORE, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H21 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_CORE_266_4_H21_4 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_CORE_266_4_H21_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_DDR
 *         PMHAL_PRCM_DPLL_POST_DIV_H11 = 8
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_DDR_200_4_H11_8 =
{PMHAL_PRCM_DPLL_POST_DIV_H11, 8U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_DDR, M = 200, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H11 = 8
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_DDR_200_4_H11_8 =
{200U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_DDR_200_4_H11_8, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_DDR
 *         PMHAL_PRCM_DPLL_POST_DIV_H11 = 8
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_DDR_266_4_H11_8 =
{PMHAL_PRCM_DPLL_POST_DIV_H11, 8U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_DDR, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H11 = 8
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_DDR_266_4_H11_8 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_DDR_266_4_H11_8, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_DDR
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_DDR_200_4_M2_2 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 2U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_DDR, M = 200, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_DDR_200_4_M2_2 =
{200U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_DDR_200_4_M2_2, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_DDR
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_DDR_266_4_M2_2 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 2U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_DDR, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_DDR_266_4_M2_2 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_DDR_266_4_M2_2, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_GMAC
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_M2_4 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_GMAC, M = 250, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_GMAC_250_4_M2_4 =
{250U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_M2_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_GMAC
 *         PMHAL_PRCM_DPLL_POST_DIV_H12 = 8
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_H12_8 =
{PMHAL_PRCM_DPLL_POST_DIV_H12, 8U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_GMAC, M = 250, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H12 = 8
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_GMAC_250_4_H12_8 =
{250U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_H12_8, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_GMAC
 *         PMHAL_PRCM_DPLL_POST_DIV_H11 = 40
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_H11_40 =
{PMHAL_PRCM_DPLL_POST_DIV_H11, 40U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_GMAC, M = 250, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H11 = 40
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_GMAC_250_4_H11_40 =
{250U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_H11_40, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_GMAC
 *         PMHAL_PRCM_DPLL_POST_DIV_H13 = 10
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_H13_10 =
{PMHAL_PRCM_DPLL_POST_DIV_H13, 10U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_GMAC, M = 250, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H13 = 10
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_GMAC_250_4_H13_10 =
{250U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_H13_10, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_GMAC
 *         PMHAL_PRCM_DPLL_POST_DIV_M3 = 10
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_M3_10 =
{PMHAL_PRCM_DPLL_POST_DIV_M3, 10U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_GMAC, M = 250, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M3 = 10
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_GMAC_250_4_M3_10 =
{250U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_M3_10, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_GMAC
 *         PMHAL_PRCM_DPLL_POST_DIV_H14 = 25
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_H14_25 =
{PMHAL_PRCM_DPLL_POST_DIV_H14, 25U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_GMAC, M = 250, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H14 = 25
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_GMAC_250_4_H14_25 =
{250U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_GMAC_250_4_H14_25, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_GPU
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_GPU_200_3_M2_2 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 2U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_GPU, M = 200, N = 3
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_GPU_200_3_M2_2 =
{200U, 3U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_GPU_200_3_M2_2, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_IVA
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 3
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_IVA_233_3_M2_3 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 3U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_IVA, M = 233, N = 3
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 3
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_IVA_233_3_M2_3 =
{233U, 3U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_IVA_233_3_M2_3, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_IVA
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_IVA_172_3_M2_2 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 2U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_IVA, M = 172, N = 3
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_IVA_172_3_M2_2 =
{172U, 3U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_IVA_172_3_M2_2, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_IVA
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_IVA_266_4_M2_2 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 2U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_IVA, M = 266, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_IVA_266_4_M2_2 =
{266U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_IVA_266_4_M2_2, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_PER
 *         PMHAL_PRCM_DPLL_POST_DIV_M2X2 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_PER_96_4_M2X2_4 =
{PMHAL_PRCM_DPLL_POST_DIV_M2X2, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_PER, M = 96, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2X2 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_PER_96_4_M2X2_4 =
{96U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_PER_96_4_M2X2_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_PER
 *         PMHAL_PRCM_DPLL_POST_DIV_H12 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_PER_96_4_H12_4 =
{PMHAL_PRCM_DPLL_POST_DIV_H12, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_PER, M = 96, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H12 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_PER_96_4_H12_4 =
{96U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_PER_96_4_H12_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_PER
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_PER_96_4_M2_4 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_PER, M = 96, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_PER_96_4_M2_4 =
{96U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_PER_96_4_M2_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_PER
 *         PMHAL_PRCM_DPLL_POST_DIV_H11 = 3
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_PER_96_4_H11_3 =
{PMHAL_PRCM_DPLL_POST_DIV_H11, 3U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_PER, M = 96, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H11 = 3
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_PER_96_4_H11_3 =
{96U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_PER_96_4_H11_3, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_PER
 *         PMHAL_PRCM_DPLL_POST_DIV_H13 = 4
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_PER_96_4_H13_4 =
{PMHAL_PRCM_DPLL_POST_DIV_H13, 4U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_PER, M = 96, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_H13 = 4
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_PER_96_4_H13_4 =
{96U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_PER_96_4_H13_4, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_USB
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_USB_480_9_M2_2 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 2U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_USB, M = 480, N = 9
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_USB_480_9_M2_2 =
{480U, 9U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_USB_480_9_M2_2, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_USB
 *         PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_USB_480_9_DCO_LDO_1 =
{PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_USB, M = 480, N = 9
 *         PMHAL_PRCM_DPLL_POST_DIV_DCO_LDO = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_USB_480_9_DCO_LDO_1 =
{480U, 9U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_USB_480_9_DCO_LDO_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_DSP
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_DSP_150_4_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_DSP, M = 150, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_DSP_150_4_M2_1 =
{150U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_DSP_150_4_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_DSP
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_DSP_175_4_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_DSP, M = 175, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_DSP_175_4_M2_1 =
{175U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_DSP_175_4_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_DSP
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_DSP_225_5_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_DSP, M = 225, N = 5
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_DSP_225_5_M2_1 =
{225U, 5U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_DSP_225_5_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_DSP
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_DSP_250_4_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_DSP, M = 250, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_DSP_250_4_M2_1 =
{250U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_DSP_250_4_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_EVE
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_EVE_214_3_M2_2 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 2U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_EVE, M = 214, N = 3
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_EVE_214_3_M2_2 =
{214U, 3U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_EVE_214_3_M2_2, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_EVE
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_EVE_260_3_M2_2 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 2U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_EVE, M = 260, N = 3
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 2
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_EVE_260_3_M2_2 =
{260U, 3U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_EVE_260_3_M2_2, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_EVE
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_EVE_180_3_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_EVE, M = 180, N = 3
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_EVE_180_3_M2_1 =
{180U, 3U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_EVE_180_3_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_MPU
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_MPU_250_9_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_MPU, M = 250, N = 9
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_MPU_250_9_M2_1 =
{250U, 9U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_MPU_250_9_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_MPU
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_MPU_375_9_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_MPU, M = 375, N = 9
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_MPU_375_9_M2_1 =
{375U, 9U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_MPU_375_9_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_MPU
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_MPU_500_9_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_MPU, M = 500, N = 9
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_MPU_500_9_M2_1 =
{500U, 9U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_MPU_500_9_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_MPU
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_MPU_294_4_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_MPU, M = 294, N = 4
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_MPU_294_4_M2_1 =
{294U, 4U, 0U,
 &postDiv_PMHAL_PRCM_DPLL_MPU_294_4_M2_1, 1U, 0U};

/**
 * \brief  Post divider Configuration for PMHAL_PRCM_DPLL_MPU
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmPllPostDivValue_t postDiv_PMHAL_PRCM_DPLL_MPU_600_7_M2_1 =
{PMHAL_PRCM_DPLL_POST_DIV_M2, 1U};
/**
 * \brief  DPLL Configuration for PMHAL_PRCM_DPLL_MPU, M = 600, N = 7
 *         PMHAL_PRCM_DPLL_POST_DIV_M2 = 1
 */
pmhalPrcmDpllConfig_t PMHAL_PRCM_DPLL_MPU_600_7_M2_1 =
{600U, 7U, 1U,
 &postDiv_PMHAL_PRCM_DPLL_MPU_600_7_M2_1, 1U, 0U};

/* -------------------------------------------------------------------------- */
/*              Mux and Divider Configuration Structures                      */
/* -------------------------------------------------------------------------- */

/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_ATL_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_ATL_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_ATL_GFCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_ATL_GFCLK_266000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_ATL_GFCLK_MUX,
     PMHAL_PRCM_DIV_L3_ICLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_ATL_GFCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_ATL_GFCLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_ATL_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_ATL_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_ATL_GFCLK_MUX,
     PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX},
    {PMHAL_PRCM_MUX_ATL_DPLL_CLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_ATL_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_ATL_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_ATL_GFCLK_MUX,
     PMHAL_PRCM_DPLL_ABE},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_ABE_GICLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_ABE_GICLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_ABE_GICLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_ABE_GICLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_CLKOUTMUX1_CLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX,
     PMHAL_PRCM_DIV_SYS_CLK1_DCLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_CLKOUTMUX1_CLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_SYS_CLK1_DCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_CLKOUTMUX2_CLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX,
     PMHAL_PRCM_DIV_SYS_CLK1_DCLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_CLKOUTMUX2_CLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_SYS_CLK1_DCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     32}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     32}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     32}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     32}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     32}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_COREAON_32K_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_COREAON_32K_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_DMA_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_DMA_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_HDMI_DPLL_CLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_HDMI_DPLL_CLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_HDMI_DPLL_CLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_HDMI_DPLL_CLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_HDMI_DPLL_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_VIDEO1_DPLL_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_VIDEO2_DPLL_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_EMIF_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_EMIF_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_EVE1_GFCLK run
 *         at 535000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_EVE1_GFCLK_535000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     PMHAL_PRCM_DPLL_EVE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_EVE1_GFCLK run
 *         at 650000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_EVE1_GFCLK_650000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     PMHAL_PRCM_DPLL_EVE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_EVE1_GFCLK run
 *         at 900000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_EVE1_GFCLK_900000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     PMHAL_PRCM_DPLL_EVE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_EVE2_GFCLK run
 *         at 535000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_EVE2_GFCLK_535000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     PMHAL_PRCM_DPLL_EVE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_EVE2_GFCLK run
 *         at 650000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_EVE2_GFCLK_650000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX,
     PMHAL_PRCM_DPLL_EVE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GMAC_RFT_CLK run
 *         at 266000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GMAC_RFT_CLK_266000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX,
     PMHAL_PRCM_DIV_L3_ICLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_GMAC_RFT_CLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_GMAC_RFT_CLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GMAC_RFT_CLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GMAC_RFT_CLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX,
     PMHAL_PRCM_DPLL_ABE},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_RMII_50MHZ_CLK run
 *         at 50000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_RMII_50MHZ_CLK_50000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_RMII_REF_CLK_MUX,
     PMHAL_PRCM_DPLL_GMAC}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_RGMII_5MHZ_CLK run
 *         at 5000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_RGMII_5MHZ_CLK_5000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_RMII_REF_CLK_MUX,
     PMHAL_PRCM_DPLL_GMAC}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GPU_CORE_GCLK run
 *         at 425600000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GPU_CORE_GCLK_425600000_muxSel[] =
{
    {PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GPU_CORE_GCLK run
 *         at 500000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GPU_CORE_GCLK_500000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX,
     PMHAL_PRCM_DPLL_GPU}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GPU_CORE_GCLK run
 *         at 532000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GPU_CORE_GCLK_532000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_GPU_CORE_GCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GPU_HYD_GCLK run
 *         at 425600000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GPU_HYD_GCLK_425600000_muxSel[] =
{
    {PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GPU_HYD_GCLK run
 *         at 500000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GPU_HYD_GCLK_500000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX,
     PMHAL_PRCM_DPLL_GPU}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GPU_HYD_GCLK run
 *         at 532000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GPU_HYD_GCLK_532000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_GPU_HYD_GCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_IPU_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_IPU_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_225792000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_225792000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_112896000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_112896000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER5_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER5_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER5_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER5_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER5_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER5_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER5_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER5_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER6_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER6_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER6_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER6_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER6_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER6_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER6_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER6_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER7_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER7_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER7_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER7_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER7_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER7_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER7_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER7_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER8_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER8_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER8_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER8_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER8_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER8_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER8_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER8_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART6_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART6_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART6_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART6_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART6_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART6_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_IPU1_GFCLK run
 *         at 212800000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_IPU1_GFCLK_212800000_muxSel[] =
{
    {PMHAL_PRCM_MUX_IPU1_GFCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INIT_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INIT_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INIT_L4_GICLK run
 *         at 133000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INIT_L4_GICLK_133000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2},
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC1_FCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_192000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC1_FCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_96000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC1_FCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_96000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC1_FCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC1_FCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_48000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC1_FCLK,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 128000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_128000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC1_FCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 128000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_128000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC1_FCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 64000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_64000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC1_FCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 64000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_64000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC1_FCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 32000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_32000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC1_FCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC1_GFCLK run
 *         at 32000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_32000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC1_FCLK,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INIT_32K_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INIT_32K_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC2_FCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_192000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC2_FCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_96000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC2_FCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_96000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC2_FCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC2_FCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_48000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC2_FCLK,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 128000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_128000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC2_FCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 128000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_128000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC2_FCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 64000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_64000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC2_FCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 64000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_64000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC2_FCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 32000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_32000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC2_FCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC2_GFCLK run
 *         at 32000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_32000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC2_FCLK,
     4}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 2500000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_2500000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 2500000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_2500000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 1250000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1250000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 1250000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1250000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 625000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_625000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 625000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_625000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     32}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 7056000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_7056000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 7056000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_7056000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     8},
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 3528000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_3528000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 3528000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_3528000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     16},
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 1764000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1764000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK run
 *         at 1764000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1764000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     32},
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 2500000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_2500000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 2500000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_2500000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 1250000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1250000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 1250000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1250000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 625000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_625000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 625000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_625000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     32}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 7056000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_7056000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 7056000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_7056000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     8},
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 3528000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_3528000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 3528000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_3528000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     16},
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 1764000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1764000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK run
 *         at 1764000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1764000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3INSTR_TS_GCLK,
     32},
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3INSTR_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3INSTR_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK run
 *         at 133000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK_133000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2},
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4CFG_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4CFG_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4CFG_L4_GICLK run
 *         at 133000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4CFG_L4_GICLK_133000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2},
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4PER_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4PER_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4PER_L4_GICLK run
 *         at 133000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4PER_L4_GICLK_133000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2},
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER10_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER10_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER10_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER10_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER10_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER10_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER10_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER10_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER10_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER11_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER11_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER11_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER11_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER11_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER11_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER11_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER11_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER11_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER2_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER2_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER2_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER2_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER2_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER2_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER2_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER2_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER3_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER3_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER3_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER3_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER3_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER3_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER3_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER3_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER4_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER4_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER4_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER4_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER4_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER4_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER4_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER4_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER9_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER9_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER9_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER9_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER9_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER9_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER9_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER9_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER9_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART1_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART1_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART1_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART1_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART1_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART1_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART2_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART2_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART2_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART2_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART2_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART2_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART3_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART3_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART3_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART3_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART3_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART3_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART4_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART4_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART4_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART4_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART4_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART4_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART5_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART5_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART5_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART5_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART5_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART5_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_GPIO_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_GPIO_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_L4PER_32K_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_L4PER_32K_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC3_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_192000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC3_GFCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_96000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC3_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_96000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC3_GFCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC3_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_48000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC3_GFCLK,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC3_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 24000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_24000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC3_GFCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 12000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_12000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC3_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC3_GFCLK run
 *         at 12000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_12000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC3_GFCLK,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC4_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_192000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC4_GFCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_96000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC4_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_96000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC4_GFCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC4_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_48000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC4_GFCLK,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC4_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 24000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_24000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC4_GFCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 12000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_12000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MMC4_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MMC4_GFCLK run
 *         at 12000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_12000000_divSel[] =
{
    {PMHAL_PRCM_DIV_MMC4_GFCLK,
     4}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4PER2_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4PER2_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART7_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART7_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART7_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART7_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART7_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART7_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART8_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART8_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART8_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART8_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART8_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART8_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART9_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART9_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART9_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART9_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART9_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART9_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_225792000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_225792000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_112896000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_112896000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_225792000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_225792000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_112896000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_112896000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AHCLKX_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_225792000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_225792000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_112896000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_112896000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP4_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AHCLKX_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_225792000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_225792000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_112896000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_112896000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP5_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AHCLKX_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_225792000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_225792000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_112896000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_112896000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP6_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AHCLKX_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_225792000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_225792000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_112896000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_112896000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP7_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_24M_FCLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX,
     PMHAL_PRCM_DIV_ABE_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX run
 *         at 24000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_24000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX,
     PMHAL_PRCM_DIV_FUNC_24M_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AHCLKX_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_225792000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 225792000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_225792000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_112896000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 112896000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_112896000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     8}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_MCASP8_AUX_GFCLK_MUX,
     PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 128000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_128000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_QSPI_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 128000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_128000000_divSel[] =
{
    {PMHAL_PRCM_DIV_QSPI_GFCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 64000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_64000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_QSPI_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 64000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_64000000_divSel[] =
{
    {PMHAL_PRCM_DIV_QSPI_GFCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 32000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_32000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_QSPI_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 32000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_32000000_divSel[] =
{
    {PMHAL_PRCM_DIV_QSPI_GFCLK,
     4}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_QSPI_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_192000000_divSel[] =
{
    {PMHAL_PRCM_DIV_QSPI_GFCLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_96000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_QSPI_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 96000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_96000000_divSel[] =
{
    {PMHAL_PRCM_DIV_QSPI_GFCLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_QSPI_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_QSPI_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_48000000_divSel[] =
{
    {PMHAL_PRCM_DIV_QSPI_GFCLK,
     4}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4PER3_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4PER3_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4PER3_L4_GICLK run
 *         at 133000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4PER3_L4_GICLK_133000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2},
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER13_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER13_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER13_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER13_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER13_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER13_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER13_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER13_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER13_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER14_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER14_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER14_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER14_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER14_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER14_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER14_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER14_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER14_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER15_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER15_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER15_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER15_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER15_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER15_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER15_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER15_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER15_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER16_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER16_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER16_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER16_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER16_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER16_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER16_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER16_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER16_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4SEC_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4SEC_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_L4SEC_L4_GICLK run
 *         at 133000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_L4SEC_L4_GICLK_133000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2},
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_PCIE_32K_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_PCIE_32K_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_PCIE_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_PCIE_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_RTC_L4_GICLK run
 *         at 133000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_RTC_L4_GICLK_133000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2},
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_RTC_AUX_CLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_RTC_AUX_CLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_VIP1_GCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_VIP1_GCLK_266000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_VIP1_GCLK_MUX,
     PMHAL_PRCM_DIV_L3_ICLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_VIP1_GCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_VIP1_GCLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_VIP2_GCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_VIP2_GCLK_266000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_VIP2_GCLK_MUX,
     PMHAL_PRCM_DIV_L3_ICLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_VIP2_GCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_VIP2_GCLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_VIP3_GCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_VIP3_GCLK_266000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_VIP3_GCLK_MUX,
     PMHAL_PRCM_DIV_L3_ICLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_VIP3_GCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_VIP3_GCLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_VPE_GCLK run
 *         at 266000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_VPE_GCLK_266000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_VPE_GCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_ADC_L3_GICLK run
 *         at 266000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_ADC_L3_GICLK_266000000_divSel[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_FUNC_32K_CLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_FUNC_32K_CLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_WKUPAON_GICLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_WKUPAON_GICLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_WKUPAON_GICLK run
 *         at 56448000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_WKUPAON_GICLK_56448000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_WKUPAON_GICLK run
 *         at 56448000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_WKUPAON_GICLK_56448000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     16}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_WKUPAON_GICLK run
 *         at 28224000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_WKUPAON_GICLK_28224000_muxSel[] =
{
    {PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX,
     PMHAL_PRCM_DIV_ABE_LP_CLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_WKUPAON_GICLK run
 *         at 28224000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_WKUPAON_GICLK_28224000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_LP_CLK,
     32}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_DCAN1_SYS_CLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_DCAN1_SYS_CLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_DCAN1_SYS_CLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_DCAN1_SYS_CLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER1_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_20000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER1_GFCLK run
 *         at 20000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_20000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     1}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER1_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_10000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
     PMHAL_PRCM_DIV_TIMER_SYS_CLK}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER1_GFCLK run
 *         at 10000000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_10000000_divSel[] =
{
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER1_GFCLK run
 *         at 32786 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_32786_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
     PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     PMHAL_PRCM_DIV_FUNC_32K_CLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER1_GFCLK run
 *         at 22579200 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_22579200_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_TIMER1_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_451584000_muxSel[] =
{
    {PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX,
     PMHAL_PRCM_DIV_ABE_GICLK},
    {PMHAL_PRCM_MUX_ABE_DPLL_REF_CLK_MUX,
     PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX},
    {PMHAL_PRCM_MUX_ABE_DPLL_SYS_CLK_MUX,
     PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2}
};
/**
 * \brief  List of the Dividers and their corresponding
 *         values to make the clock PMHAL_PRCM_CLK_TIMER1_GFCLK run
 *         at 451584000 Hz.
 */
pmlibClockRateDivConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_451584000_divSel[] =
{
    {PMHAL_PRCM_DIV_ABE_CLK,
     1},
    {PMHAL_PRCM_DIV_AESS_FCLK,
     1},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     2}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART10_GFCLK run
 *         at 192000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART10_GFCLK_192000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART10_GFCLK_MUX,
     PMHAL_PRCM_DPLL_PER}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_UART10_GFCLK run
 *         at 48000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_UART10_GFCLK_48000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_UART10_GFCLK_MUX,
     PMHAL_PRCM_DIV_FUNC_48M_FCLK}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_ISS_GCLK run
 *         at 355000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_ISS_GCLK_355000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_ISS_GFCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_ISS_GCLK run
 *         at 425600000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_ISS_GCLK_425600000_muxSel[] =
{
    {PMHAL_PRCM_MUX_ISS_GFCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/**
 * \brief  List of the Muxes and their corresponding Parent
 *         Select to make the clock PMHAL_PRCM_CLK_ISS_GCLK run
 *         at 532000000 Hz.
 */
pmlibClockRateMuxConfig_t PMHAL_PRCM_CLK_ISS_GCLK_532000000_muxSel[] =
{
    {PMHAL_PRCM_MUX_ISS_GFCLK_MUX,
     PMHAL_PRCM_DPLL_CORE}
};
/* -------------------------------------------------------------------------- */
/*              Frequency Configuration Structures                            */
/* -------------------------------------------------------------------------- */

/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ATL_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ATL_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_ATL_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ATL_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ATL_GFCLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ATL_GFCLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    PMHAL_PRCM_CLK_ATL_GFCLK_266000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ATL_GFCLK_266000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_ATL_GFCLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ATL_GFCLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ATL_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ATL_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_ATL_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ATL_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ATL_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ATL_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_ATL_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ATL_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ABE_GICLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ABE_GICLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_ABE_GICLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ABE_GICLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_ABE_GICLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ABE_GICLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_CLKOUTMUX1_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_CLKOUTMUX2_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INIT_60M_FCLK
 *         for the frequency 60000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INIT_60M_FCLK_60000000 =
{
    PMHAL_PRCM_DPLL_USB,
    &PMHAL_PRCM_DPLL_USB_480_9_M2_2,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_COREAON_32K_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_COREAON_32K_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_COREAON_32K_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_COREAON_32K_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DMA_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DMA_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_DMA_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DMA_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSP1_GFCLK
 *         for the frequency 600000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSP1_GFCLK_600000000 =
{
    PMHAL_PRCM_DPLL_DSP,
    &PMHAL_PRCM_DPLL_DSP_150_4_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSP1_GFCLK
 *         for the frequency 700000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSP1_GFCLK_700000000 =
{
    PMHAL_PRCM_DPLL_DSP,
    &PMHAL_PRCM_DPLL_DSP_175_4_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSP1_GFCLK
 *         for the frequency 750000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSP1_GFCLK_750000000 =
{
    PMHAL_PRCM_DPLL_DSP,
    &PMHAL_PRCM_DPLL_DSP_225_5_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSP1_GFCLK
 *         for the frequency 1000000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSP1_GFCLK_1000000000 =
{
    PMHAL_PRCM_DPLL_DSP,
    &PMHAL_PRCM_DPLL_DSP_250_4_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSP2_GFCLK
 *         for the frequency 600000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSP2_GFCLK_600000000 =
{
    PMHAL_PRCM_DPLL_DSP,
    &PMHAL_PRCM_DPLL_DSP_150_4_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSP2_GFCLK
 *         for the frequency 700000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSP2_GFCLK_700000000 =
{
    PMHAL_PRCM_DPLL_DSP,
    &PMHAL_PRCM_DPLL_DSP_175_4_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSP2_GFCLK
 *         for the frequency 750000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSP2_GFCLK_750000000 =
{
    PMHAL_PRCM_DPLL_DSP,
    &PMHAL_PRCM_DPLL_DSP_250_4_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSP2_GFCLK
 *         for the frequency 1000000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSP2_GFCLK_1000000000 =
{
    PMHAL_PRCM_DPLL_DSP,
    &PMHAL_PRCM_DPLL_DSP_250_4_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_BB2D_GFCLK
 *         for the frequency 354666666.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_BB2D_GFCLK_354666666 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H24_6,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_HDMI_CEC_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_HDMI_CEC_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_HDMI_PHY_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_HDMI_PHY_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DSS_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DSS_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H12_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_HDMI_DPLL_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_HDMI_DPLL_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_HDMI_DPLL_CLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_HDMI_DPLL_CLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_HDMI_DPLL_CLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_HDMI_DPLL_CLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_HDMI_DPLL_CLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_HDMI_DPLL_CLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SDVENC_GFCLK
 *         for the frequency 0.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SDVENC_GFCLK_0 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EMIF_DLL_GCLK
 *         for the frequency 200000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EMIF_DLL_GCLK_200000000 =
{
    PMHAL_PRCM_DPLL_DDR,
    &PMHAL_PRCM_DPLL_DDR_200_4_H11_8,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EMIF_DLL_GCLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EMIF_DLL_GCLK_266000000 =
{
    PMHAL_PRCM_DPLL_DDR,
    &PMHAL_PRCM_DPLL_DDR_266_4_H11_8,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EMIF_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EMIF_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_EMIF_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EMIF_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EMIF_PHY_GCLK
 *         for the frequency 400000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EMIF_PHY_GCLK_400000000 =
{
    PMHAL_PRCM_DPLL_DDR,
    &PMHAL_PRCM_DPLL_DDR_200_4_M2_2,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EMIF_PHY_GCLK
 *         for the frequency 532000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EMIF_PHY_GCLK_532000000 =
{
    PMHAL_PRCM_DPLL_DDR,
    &PMHAL_PRCM_DPLL_DDR_266_4_M2_2,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EVE1_GFCLK
 *         for the frequency 535000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EVE1_GFCLK_535000000 =
{
    PMHAL_PRCM_DPLL_EVE,
    &PMHAL_PRCM_DPLL_EVE_214_3_M2_2,
    PMHAL_PRCM_CLK_EVE1_GFCLK_535000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EVE1_GFCLK_535000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EVE1_GFCLK
 *         for the frequency 650000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EVE1_GFCLK_650000000 =
{
    PMHAL_PRCM_DPLL_EVE,
    &PMHAL_PRCM_DPLL_EVE_260_3_M2_2,
    PMHAL_PRCM_CLK_EVE1_GFCLK_650000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EVE1_GFCLK_650000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EVE1_GFCLK
 *         for the frequency 900000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EVE1_GFCLK_900000000 =
{
    PMHAL_PRCM_DPLL_EVE,
    &PMHAL_PRCM_DPLL_EVE_180_3_M2_1,
    PMHAL_PRCM_CLK_EVE1_GFCLK_900000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EVE1_GFCLK_900000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EVE2_GFCLK
 *         for the frequency 535000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EVE2_GFCLK_535000000 =
{
    PMHAL_PRCM_DPLL_EVE,
    &PMHAL_PRCM_DPLL_EVE_214_3_M2_2,
    PMHAL_PRCM_CLK_EVE2_GFCLK_535000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EVE2_GFCLK_535000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EVE2_GFCLK
 *         for the frequency 650000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EVE2_GFCLK_650000000 =
{
    PMHAL_PRCM_DPLL_EVE,
    &PMHAL_PRCM_DPLL_EVE_260_3_M2_2,
    PMHAL_PRCM_CLK_EVE2_GFCLK_650000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EVE2_GFCLK_650000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GMAC_RFT_CLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GMAC_RFT_CLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    PMHAL_PRCM_CLK_GMAC_RFT_CLK_266000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GMAC_RFT_CLK_266000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_GMAC_RFT_CLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GMAC_RFT_CLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GMAC_RFT_CLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GMAC_RFT_CLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_GMAC_RFT_CLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GMAC_RFT_CLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GMAC_MAIN_CLK
 *         for the frequency 125000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GMAC_MAIN_CLK_125000000 =
{
    PMHAL_PRCM_DPLL_GMAC,
    &PMHAL_PRCM_DPLL_GMAC_250_4_M2_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GMII_250MHZ_CLK
 *         for the frequency 250000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GMII_250MHZ_CLK_250000000 =
{
    PMHAL_PRCM_DPLL_GMAC,
    &PMHAL_PRCM_DPLL_GMAC_250_4_H12_8,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_RMII_50MHZ_CLK
 *         for the frequency 50000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_RMII_50MHZ_CLK_50000000 =
{
    PMHAL_PRCM_DPLL_GMAC,
    &PMHAL_PRCM_DPLL_GMAC_250_4_H11_40,
    PMHAL_PRCM_CLK_RMII_50MHZ_CLK_50000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_RMII_50MHZ_CLK_50000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_RGMII_5MHZ_CLK
 *         for the frequency 5000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_RGMII_5MHZ_CLK_5000000 =
{
    PMHAL_PRCM_DPLL_GMAC,
    &PMHAL_PRCM_DPLL_GMAC_250_4_H11_40,
    PMHAL_PRCM_CLK_RGMII_5MHZ_CLK_5000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_RGMII_5MHZ_CLK_5000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GPU_CORE_GCLK
 *         for the frequency 425600000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GPU_CORE_GCLK_425600000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H14_5,
    PMHAL_PRCM_CLK_GPU_CORE_GCLK_425600000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPU_CORE_GCLK_425600000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GPU_CORE_GCLK
 *         for the frequency 500000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GPU_CORE_GCLK_500000000 =
{
    PMHAL_PRCM_DPLL_GPU,
    &PMHAL_PRCM_DPLL_GPU_200_3_M2_2,
    PMHAL_PRCM_CLK_GPU_CORE_GCLK_500000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPU_CORE_GCLK_500000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GPU_CORE_GCLK
 *         for the frequency 532000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GPU_CORE_GCLK_532000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H14_4,
    PMHAL_PRCM_CLK_GPU_CORE_GCLK_532000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPU_CORE_GCLK_532000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GPU_HYD_GCLK
 *         for the frequency 425600000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GPU_HYD_GCLK_425600000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H14_5,
    PMHAL_PRCM_CLK_GPU_HYD_GCLK_425600000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPU_HYD_GCLK_425600000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GPU_HYD_GCLK
 *         for the frequency 500000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GPU_HYD_GCLK_500000000 =
{
    PMHAL_PRCM_DPLL_GPU,
    &PMHAL_PRCM_DPLL_GPU_200_3_M2_2,
    PMHAL_PRCM_CLK_GPU_HYD_GCLK_500000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPU_HYD_GCLK_500000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GPU_HYD_GCLK
 *         for the frequency 532000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GPU_HYD_GCLK_532000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H14_4,
    PMHAL_PRCM_CLK_GPU_HYD_GCLK_532000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPU_HYD_GCLK_532000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_IPU_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_IPU_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_IPU_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_IPU_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_IPU_96M_GFCLK
 *         for the frequency 96000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_IPU_96M_GFCLK_96000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKR
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP1_AHCLKR_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AHCLKR_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKR
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP1_AHCLKR_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AHCLKR_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKR
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP1_AHCLKR_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AHCLKR_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKR
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP1_AHCLKR_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKR
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP1_AHCLKR_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKX
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP1_AHCLKX_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AHCLKX_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKX
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP1_AHCLKX_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AHCLKX_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKX
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP1_AHCLKX_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AHCLKX_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKX
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP1_AHCLKX_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AHCLKX
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP1_AHCLKX_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK
 *         for the frequency 225792000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_225792000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_225792000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_225792000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_225792000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_225792000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK
 *         for the frequency 112896000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_112896000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_112896000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_112896000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_112896000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_112896000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER5_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER5_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER5_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER5_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER5_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER5_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER5_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER5_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER5_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER5_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER5_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER5_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER5_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER5_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER6_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER6_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER6_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER6_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER6_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER6_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER6_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER6_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER6_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER6_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER6_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER6_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER6_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER6_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER7_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER7_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER7_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER7_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER7_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER7_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER7_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER7_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER7_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER7_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER7_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER7_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER7_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER7_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER8_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER8_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER8_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER8_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER8_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER8_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER8_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER8_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER8_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER8_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER8_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER8_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER8_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER8_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART6_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART6_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART6_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART6_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART6_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART6_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART6_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART6_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_IPU1_GFCLK
 *         for the frequency 212800000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_IPU1_GFCLK_212800000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H22_5,
    PMHAL_PRCM_CLK_IPU1_GFCLK_212800000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_IPU1_GFCLK_212800000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_IPU2_GFCLK
 *         for the frequency 212800000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_IPU2_GFCLK_212800000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H22_5,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_IVA_GCLK
 *         for the frequency 388333333.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_IVA_GCLK_388333333 =
{
    PMHAL_PRCM_DPLL_IVA,
    &PMHAL_PRCM_DPLL_IVA_233_3_M2_3,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_IVA_GCLK
 *         for the frequency 430000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_IVA_GCLK_430000000 =
{
    PMHAL_PRCM_DPLL_IVA,
    &PMHAL_PRCM_DPLL_IVA_172_3_M2_2,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_IVA_GCLK
 *         for the frequency 532000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_IVA_GCLK_532000000 =
{
    PMHAL_PRCM_DPLL_IVA,
    &PMHAL_PRCM_DPLL_IVA_266_4_M2_2,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INIT_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INIT_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L3INIT_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INIT_L4_GICLK
 *         for the frequency 133000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INIT_L4_GICLK_133000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L3INIT_L4_GICLK_133000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_L4_GICLK_133000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC1_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC1_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC1_GFCLK_192000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_192000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC1_GFCLK
 *         for the frequency 96000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_96000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC1_GFCLK_96000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_96000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC1_GFCLK_96000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_96000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC1_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC1_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC1_GFCLK_48000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_48000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC1_GFCLK
 *         for the frequency 128000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_128000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_MMC1_GFCLK_128000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_128000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC1_GFCLK_128000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_128000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC1_GFCLK
 *         for the frequency 64000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_64000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_MMC1_GFCLK_64000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_64000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC1_GFCLK_64000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_64000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC1_GFCLK
 *         for the frequency 32000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC1_GFCLK_32000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_MMC1_GFCLK_32000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_32000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC1_GFCLK_32000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_32000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INIT_32K_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INIT_32K_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_L3INIT_32K_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_32K_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC2_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC2_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC2_GFCLK_192000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_192000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC2_GFCLK
 *         for the frequency 96000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_96000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC2_GFCLK_96000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_96000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC2_GFCLK_96000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_96000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC2_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC2_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC2_GFCLK_48000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_48000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC2_GFCLK
 *         for the frequency 128000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_128000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_MMC2_GFCLK_128000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_128000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC2_GFCLK_128000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_128000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC2_GFCLK
 *         for the frequency 64000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_64000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_MMC2_GFCLK_64000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_64000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC2_GFCLK_64000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_64000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC2_GFCLK
 *         for the frequency 32000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC2_GFCLK_32000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_MMC2_GFCLK_32000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_32000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC2_GFCLK_32000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_32000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INIT_48M_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INIT_48M_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SATA_REF_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SATA_REF_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INIT_960M_GFCLK
 *         for the frequency 960000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INIT_960M_GFCLK_960000000 =
{
    PMHAL_PRCM_DPLL_USB,
    &PMHAL_PRCM_DPLL_USB_480_9_DCO_LDO_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_TS_GCLK
 *         for the frequency 2500000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_2500000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_2500000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_2500000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_2500000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_2500000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_TS_GCLK
 *         for the frequency 1250000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1250000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1250000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1250000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1250000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1250000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_TS_GCLK
 *         for the frequency 625000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_625000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_625000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_625000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_625000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_625000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_TS_GCLK
 *         for the frequency 7056000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_7056000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_7056000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_7056000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_7056000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_7056000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_TS_GCLK
 *         for the frequency 3528000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_3528000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_3528000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_3528000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_3528000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_3528000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_TS_GCLK
 *         for the frequency 1764000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1764000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1764000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1764000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1764000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1764000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK
 *         for the frequency 2500000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_2500000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_2500000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_2500000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_2500000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_2500000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK
 *         for the frequency 1250000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1250000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1250000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1250000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1250000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1250000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK
 *         for the frequency 625000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_625000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_625000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_625000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_625000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_625000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK
 *         for the frequency 7056000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_7056000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_7056000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_7056000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_7056000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_7056000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK
 *         for the frequency 3528000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_3528000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_3528000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_3528000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_3528000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_3528000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK
 *         for the frequency 1764000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1764000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1764000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1764000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1764000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1764000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3INSTR_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3INSTR_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L3INSTR_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK
 *         for the frequency 133000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK_133000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK_133000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK_133000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4CFG_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4CFG_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4CFG_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4CFG_L4_GICLK
 *         for the frequency 133000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4CFG_L4_GICLK_133000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4CFG_L4_GICLK_133000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4CFG_L4_GICLK_133000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4PER_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4PER_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4PER_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PER_96M_GFCLK
 *         for the frequency 96000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PER_96M_GFCLK_96000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4PER_L4_GICLK
 *         for the frequency 133000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4PER_L4_GICLK_133000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4PER_L4_GICLK_133000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER_L4_GICLK_133000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER10_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER10_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER10_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER10_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER10_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER10_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER10_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER10_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER10_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER10_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER10_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER10_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER10_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER10_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER11_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER11_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER11_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER11_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER11_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER11_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER11_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER11_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER11_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER11_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER11_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER11_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER11_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER11_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER2_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER2_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER2_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER2_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER2_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER2_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER2_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER2_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER2_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER2_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER2_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER2_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER2_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER2_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER3_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER3_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER3_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER3_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER3_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER3_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER3_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER3_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER3_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER3_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER3_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER3_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER3_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER3_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER4_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER4_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER4_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER4_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER4_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER4_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER4_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER4_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER4_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER4_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER4_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER4_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER4_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER4_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER9_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER9_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER9_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER9_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER9_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER9_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER9_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER9_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER9_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER9_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER9_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER9_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER9_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER9_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PER_12M_GFCLK
 *         for the frequency 12000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PER_12M_GFCLK_12000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PER_48M_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PER_48M_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART1_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART1_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART1_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART1_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART1_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART1_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART1_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART1_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART2_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART2_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART2_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART2_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART2_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART2_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART2_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART2_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART3_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART3_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART3_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART3_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART3_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART3_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART3_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART3_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART4_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART4_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART4_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART4_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART4_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART4_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART4_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART4_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART5_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART5_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART5_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART5_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART5_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART5_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART5_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART5_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_GPIO_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_GPIO_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_GPIO_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPIO_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4PER_32K_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4PER_32K_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_L4PER_32K_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER_32K_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC3_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC3_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC3_GFCLK_192000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_192000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC3_GFCLK
 *         for the frequency 96000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_96000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC3_GFCLK_96000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_96000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC3_GFCLK_96000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_96000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC3_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC3_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC3_GFCLK_48000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_48000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC3_GFCLK
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC3_GFCLK_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC3_GFCLK_24000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_24000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC3_GFCLK
 *         for the frequency 12000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC3_GFCLK_12000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC3_GFCLK_12000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_12000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC3_GFCLK_12000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_12000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC4_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC4_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC4_GFCLK_192000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_192000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC4_GFCLK
 *         for the frequency 96000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_96000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC4_GFCLK_96000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_96000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC4_GFCLK_96000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_96000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC4_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC4_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC4_GFCLK_48000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_48000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC4_GFCLK
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC4_GFCLK_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC4_GFCLK_24000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_24000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MMC4_GFCLK
 *         for the frequency 12000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MMC4_GFCLK_12000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_MMC4_GFCLK_12000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_12000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MMC4_GFCLK_12000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_12000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DCAN2_SYS_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DCAN2_SYS_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4PER2_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4PER2_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4PER2_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER2_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART7_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART7_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART7_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART7_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART7_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART7_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART7_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART7_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART8_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART8_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART8_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART8_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART8_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART8_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART8_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART8_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART9_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART9_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART9_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART9_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART9_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART9_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART9_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART9_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ICSS_IEP_CLK
 *         for the frequency 200000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ICSS_IEP_CLK_200000000 =
{
    PMHAL_PRCM_DPLL_GMAC,
    &PMHAL_PRCM_DPLL_GMAC_250_4_M3_10,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ICSS_CLK
 *         for the frequency 200000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ICSS_CLK_200000000 =
{
    PMHAL_PRCM_DPLL_GMAC,
    &PMHAL_PRCM_DPLL_GMAC_250_4_H13_10,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PER_192M_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PER_192M_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKX
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP2_AHCLKX_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AHCLKX_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKX
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP2_AHCLKX_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AHCLKX_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKX
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP2_AHCLKX_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AHCLKX_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKX
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP2_AHCLKX_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKX
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP2_AHCLKX_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKR
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP2_AHCLKR_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AHCLKR_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKR
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP2_AHCLKR_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AHCLKR_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKR
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP2_AHCLKR_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AHCLKR_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKR
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP2_AHCLKR_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AHCLKR
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP2_AHCLKR_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK
 *         for the frequency 225792000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_225792000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_225792000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_225792000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_225792000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_225792000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK
 *         for the frequency 112896000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_112896000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_112896000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_112896000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_112896000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_112896000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AHCLKX
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP3_AHCLKX_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP3_AHCLKX_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AHCLKX
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP3_AHCLKX_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP3_AHCLKX_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AHCLKX
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP3_AHCLKX_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP3_AHCLKX_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AHCLKX
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP3_AHCLKX_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AHCLKX
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP3_AHCLKX_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK
 *         for the frequency 225792000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_225792000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_225792000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_225792000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_225792000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_225792000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK
 *         for the frequency 112896000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_112896000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_112896000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_112896000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_112896000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_112896000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AHCLKX
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP4_AHCLKX_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP4_AHCLKX_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AHCLKX
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP4_AHCLKX_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP4_AHCLKX_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AHCLKX
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP4_AHCLKX_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP4_AHCLKX_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AHCLKX
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP4_AHCLKX_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AHCLKX
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP4_AHCLKX_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK
 *         for the frequency 225792000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_225792000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_225792000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_225792000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_225792000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_225792000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK
 *         for the frequency 112896000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_112896000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_112896000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_112896000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_112896000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_112896000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AHCLKX
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP5_AHCLKX_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP5_AHCLKX_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AHCLKX
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP5_AHCLKX_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP5_AHCLKX_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AHCLKX
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP5_AHCLKX_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP5_AHCLKX_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AHCLKX
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP5_AHCLKX_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AHCLKX
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP5_AHCLKX_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK
 *         for the frequency 225792000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_225792000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_225792000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_225792000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_225792000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_225792000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK
 *         for the frequency 112896000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_112896000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_112896000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_112896000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_112896000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_112896000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AHCLKX
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP6_AHCLKX_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP6_AHCLKX_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AHCLKX
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP6_AHCLKX_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP6_AHCLKX_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AHCLKX
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP6_AHCLKX_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP6_AHCLKX_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AHCLKX
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP6_AHCLKX_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AHCLKX
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP6_AHCLKX_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK
 *         for the frequency 225792000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_225792000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_225792000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_225792000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_225792000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_225792000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK
 *         for the frequency 112896000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_112896000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_112896000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_112896000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_112896000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_112896000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AHCLKX
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP7_AHCLKX_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP7_AHCLKX_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AHCLKX
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP7_AHCLKX_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP7_AHCLKX_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AHCLKX
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP7_AHCLKX_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP7_AHCLKX_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AHCLKX
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP7_AHCLKX_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AHCLKX
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP7_AHCLKX_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK
 *         for the frequency 225792000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_225792000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_225792000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_225792000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_225792000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_225792000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK
 *         for the frequency 112896000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_112896000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_112896000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_112896000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_112896000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_112896000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AHCLKX
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_MCASP8_AHCLKX_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP8_AHCLKX_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AHCLKX
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP8_AHCLKX_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP8_AHCLKX_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AHCLKX
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP8_AHCLKX_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP8_AHCLKX_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AHCLKX
 *         for the frequency 24000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_24000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2_4,
    PMHAL_PRCM_CLK_MCASP8_AHCLKX_24000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_24000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AHCLKX
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_MCASP8_AHCLKX_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK
 *         for the frequency 225792000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_225792000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_225792000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_225792000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_225792000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_225792000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK
 *         for the frequency 112896000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_112896000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_112896000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_112896000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_112896000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_112896000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2_1,
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_QSPI_GFCLK
 *         for the frequency 128000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_128000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_QSPI_GFCLK_128000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_128000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_QSPI_GFCLK_128000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_128000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_QSPI_GFCLK
 *         for the frequency 64000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_64000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_QSPI_GFCLK_64000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_64000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_QSPI_GFCLK_64000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_64000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_QSPI_GFCLK
 *         for the frequency 32000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_32000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H11_3,
    PMHAL_PRCM_CLK_QSPI_GFCLK_32000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_32000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_QSPI_GFCLK_32000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_32000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_QSPI_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H13_4,
    PMHAL_PRCM_CLK_QSPI_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_QSPI_GFCLK_192000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_192000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_QSPI_GFCLK
 *         for the frequency 96000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_96000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H13_4,
    PMHAL_PRCM_CLK_QSPI_GFCLK_96000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_96000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_QSPI_GFCLK_96000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_96000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_QSPI_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_QSPI_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_H13_4,
    PMHAL_PRCM_CLK_QSPI_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_QSPI_GFCLK_48000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_48000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4PER3_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4PER3_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4PER3_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER3_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4PER3_L4_GICLK
 *         for the frequency 133000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4PER3_L4_GICLK_133000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4PER3_L4_GICLK_133000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER3_L4_GICLK_133000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER13_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER13_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER13_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER13_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER13_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER13_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER13_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER13_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER13_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER13_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER13_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER13_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER13_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER13_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER14_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER14_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER14_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER14_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER14_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER14_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER14_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER14_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER14_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER14_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER14_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER14_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER14_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER14_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER15_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER15_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER15_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER15_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER15_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER15_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER15_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER15_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER15_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER15_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER15_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER15_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER15_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER15_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER16_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER16_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER16_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER16_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER16_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER16_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER16_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER16_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER16_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER16_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER16_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER16_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER16_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER16_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4SEC_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4SEC_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4SEC_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_L4SEC_L4_GICLK
 *         for the frequency 133000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_L4SEC_L4_GICLK_133000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_L4SEC_L4_GICLK_133000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4SEC_L4_GICLK_133000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MPU_GCLK
 *         for the frequency 500000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MPU_GCLK_500000000 =
{
    PMHAL_PRCM_DPLL_MPU,
    &PMHAL_PRCM_DPLL_MPU_250_9_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MPU_GCLK
 *         for the frequency 750000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MPU_GCLK_750000000 =
{
    PMHAL_PRCM_DPLL_MPU,
    &PMHAL_PRCM_DPLL_MPU_375_9_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MPU_GCLK
 *         for the frequency 1000000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MPU_GCLK_1000000000 =
{
    PMHAL_PRCM_DPLL_MPU,
    &PMHAL_PRCM_DPLL_MPU_500_9_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MPU_GCLK
 *         for the frequency 1176000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MPU_GCLK_1176000000 =
{
    PMHAL_PRCM_DPLL_MPU,
    &PMHAL_PRCM_DPLL_MPU_294_4_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MPU_GCLK
 *         for the frequency 1500000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MPU_GCLK_1500000000 =
{
    PMHAL_PRCM_DPLL_MPU,
    &PMHAL_PRCM_DPLL_MPU_600_7_M2_1,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PCIE_32K_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PCIE_32K_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_PCIE_32K_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PCIE_32K_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PCIE_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PCIE_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_PCIE_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PCIE_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PCIE_PHY_GCLK
 *         for the frequency 0.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PCIE_PHY_GCLK_0 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK
 *         for the frequency 0.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK_0 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PCIE_REF_GFCLK
 *         for the frequency 34322580.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PCIE_REF_GFCLK_34322580 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H13_62,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_PCIE_SYS_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_PCIE_SYS_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_RTC_L4_GICLK
 *         for the frequency 133000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_RTC_L4_GICLK_133000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_RTC_L4_GICLK_133000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_RTC_L4_GICLK_133000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_RTC_AUX_CLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_RTC_AUX_CLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_RTC_AUX_CLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_RTC_AUX_CLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_VIP1_GCLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_VIP1_GCLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    PMHAL_PRCM_CLK_VIP1_GCLK_266000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP1_GCLK_266000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_VIP1_GCLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP1_GCLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_VIP2_GCLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_VIP2_GCLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    PMHAL_PRCM_CLK_VIP2_GCLK_266000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP2_GCLK_266000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_VIP2_GCLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP2_GCLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_VIP3_GCLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_VIP3_GCLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    PMHAL_PRCM_CLK_VIP3_GCLK_266000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP3_GCLK_266000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_VIP3_GCLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP3_GCLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_VPE_GCLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_VPE_GCLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H23_4,
    PMHAL_PRCM_CLK_VPE_GCLK_266000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VPE_GCLK_266000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_EMU_SYS_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_EMU_SYS_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ADC_L3_GICLK
 *         for the frequency 266000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ADC_L3_GICLK_266000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H12_4,
    NULL,
    0U,
    PMHAL_PRCM_CLK_ADC_L3_GICLK_266000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ADC_L3_GICLK_266000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_FUNC_32K_CLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_FUNC_32K_CLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_FUNC_32K_CLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_FUNC_32K_CLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_WKUPAON_GICLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_WKUPAON_GICLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_WKUPAON_GICLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_GICLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_WKUPAON_GICLK
 *         for the frequency 56448000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_WKUPAON_GICLK_56448000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_WKUPAON_GICLK_56448000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_GICLK_56448000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_WKUPAON_GICLK_56448000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_GICLK_56448000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_WKUPAON_GICLK
 *         for the frequency 28224000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_WKUPAON_GICLK_28224000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_WKUPAON_GICLK_28224000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_GICLK_28224000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_WKUPAON_GICLK_28224000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_GICLK_28224000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DCAN1_SYS_CLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DCAN1_SYS_CLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_DCAN1_SYS_CLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DCAN1_SYS_CLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_DCAN1_SYS_CLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_DCAN1_SYS_CLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_DCAN1_SYS_CLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DCAN1_SYS_CLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER1_GFCLK
 *         for the frequency 20000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_20000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER1_GFCLK_20000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_20000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER1_GFCLK_20000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_20000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER1_GFCLK
 *         for the frequency 10000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_10000000 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER1_GFCLK_10000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_10000000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER1_GFCLK_10000000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_10000000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER1_GFCLK
 *         for the frequency 32786.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_32786 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER1_GFCLK_32786_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_32786_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER1_GFCLK
 *         for the frequency 22579200.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_22579200 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    PMHAL_PRCM_CLK_TIMER1_GFCLK_22579200_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_22579200_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_TIMER1_GFCLK
 *         for the frequency 451584000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_TIMER1_GFCLK_451584000 =
{
    PMHAL_PRCM_DPLL_ABE,
    &PMHAL_PRCM_DPLL_ABE_200_9_M2X2_1,
    PMHAL_PRCM_CLK_TIMER1_GFCLK_451584000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_451584000_muxSel,
        pmlibClockRateMuxConfig_t),
    PMHAL_PRCM_CLK_TIMER1_GFCLK_451584000_divSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_451584000_divSel,
        pmlibClockRateDivConfig_t)
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_SECURE_32K_CLK
 *         for the frequency 0.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_SECURE_32K_CLK_0 =
{
    PMHAL_PRCM_DPLL_COUNT,
    NULL,
    NULL,
    0U,
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART10_GFCLK
 *         for the frequency 192000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART10_GFCLK_192000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART10_GFCLK_192000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART10_GFCLK_192000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_UART10_GFCLK
 *         for the frequency 48000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_UART10_GFCLK_48000000 =
{
    PMHAL_PRCM_DPLL_PER,
    &PMHAL_PRCM_DPLL_PER_96_4_M2X2_4,
    PMHAL_PRCM_CLK_UART10_GFCLK_48000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART10_GFCLK_48000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ISS_GCLK
 *         for the frequency 355000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ISS_GCLK_355000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H21_6,
    PMHAL_PRCM_CLK_ISS_GCLK_355000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ISS_GCLK_355000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ISS_GCLK
 *         for the frequency 425600000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ISS_GCLK_425600000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H21_5,
    PMHAL_PRCM_CLK_ISS_GCLK_425600000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ISS_GCLK_425600000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_ISS_GCLK
 *         for the frequency 532000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_ISS_GCLK_532000000 =
{
    PMHAL_PRCM_DPLL_CORE,
    &PMHAL_PRCM_DPLL_CORE_266_4_H21_4,
    PMHAL_PRCM_CLK_ISS_GCLK_532000000_muxSel,
    PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ISS_GCLK_532000000_muxSel,
        pmlibClockRateMuxConfig_t),
    NULL,
    0U
};
/**
 * \brief  Configuration structure for the PMHAL_PRCM_CLK_MCAN_CLK
 *         for the frequency 80000000.
 */
pmlibClockRateFreqConfig_t PMHAL_PRCM_CLK_MCAN_CLK_80000000 =
{
    PMHAL_PRCM_DPLL_GMAC,
    &PMHAL_PRCM_DPLL_GMAC_250_4_H14_25,
    NULL,
    0U,
    NULL,
    0U
};
/* -------------------------------------------------------------------------- */
/*              Frequency List for the different Clocks                       */
/* -------------------------------------------------------------------------- */

/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_ATL_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_ATL_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_ATL_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_ATL_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_ATL_GFCLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_ATL_GFCLK_266000000},
    {32786U, &PMHAL_PRCM_CLK_ATL_GFCLK_32786},
    {451584000U, &PMHAL_PRCM_CLK_ATL_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_ABE_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_ABE_GICLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_ABE_GICLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_CLKOUTMUX1_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_CLKOUTMUX2_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INIT_60M_FCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INIT_60M_FCLK_freqList[] =
{
    {60000000U, &PMHAL_PRCM_CLK_L3INIT_60M_FCLK_60000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_20000000},
    {56448000U, &PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_20000000},
    {56448000U, &PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_20000000},
    {56448000U, &PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_20000000},
    {56448000U, &PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_20000000},
    {56448000U, &PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_COREAON_32K_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_COREAON_32K_GFCLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_COREAON_32K_GFCLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK_freqList[] =
{
    {10000000U, &PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK_10000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_DMA_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_DMA_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_DMA_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_DSP1_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_DSP1_GFCLK_freqList[] =
{
    {600000000U, &PMHAL_PRCM_CLK_DSP1_GFCLK_600000000},
    {700000000U, &PMHAL_PRCM_CLK_DSP1_GFCLK_700000000},
    {750000000U, &PMHAL_PRCM_CLK_DSP1_GFCLK_750000000},
    {1000000000U, &PMHAL_PRCM_CLK_DSP1_GFCLK_1000000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_DSP2_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_DSP2_GFCLK_freqList[] =
{
    {600000000U, &PMHAL_PRCM_CLK_DSP2_GFCLK_600000000},
    {700000000U, &PMHAL_PRCM_CLK_DSP2_GFCLK_700000000},
    {750000000U, &PMHAL_PRCM_CLK_DSP2_GFCLK_750000000},
    {1000000000U, &PMHAL_PRCM_CLK_DSP2_GFCLK_1000000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_BB2D_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_BB2D_GFCLK_freqList[] =
{
    {354666666U, &PMHAL_PRCM_CLK_BB2D_GFCLK_354666666}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_HDMI_CEC_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_HDMI_CEC_GFCLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_HDMI_CEC_GFCLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_HDMI_PHY_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_HDMI_PHY_GFCLK_freqList[] =
{
    {48000000U, &PMHAL_PRCM_CLK_HDMI_PHY_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_DSS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_DSS_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_DSS_GFCLK_192000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_HDMI_DPLL_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_HDMI_DPLL_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_HDMI_DPLL_CLK_20000000},
    {22579200U, &PMHAL_PRCM_CLK_HDMI_DPLL_CLK_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_20000000},
    {22579200U, &PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_20000000},
    {22579200U, &PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_SDVENC_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_SDVENC_GFCLK_freqList[] =
{
    {0U, &PMHAL_PRCM_CLK_SDVENC_GFCLK_0}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_EMIF_DLL_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_EMIF_DLL_GCLK_freqList[] =
{
    {200000000U, &PMHAL_PRCM_CLK_EMIF_DLL_GCLK_200000000},
    {266000000U, &PMHAL_PRCM_CLK_EMIF_DLL_GCLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_EMIF_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_EMIF_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_EMIF_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_EMIF_PHY_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_EMIF_PHY_GCLK_freqList[] =
{
    {400000000U, &PMHAL_PRCM_CLK_EMIF_PHY_GCLK_400000000},
    {532000000U, &PMHAL_PRCM_CLK_EMIF_PHY_GCLK_532000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_EVE1_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_EVE1_GFCLK_freqList[] =
{
    {535000000U, &PMHAL_PRCM_CLK_EVE1_GFCLK_535000000},
    {650000000U, &PMHAL_PRCM_CLK_EVE1_GFCLK_650000000},
    {900000000U, &PMHAL_PRCM_CLK_EVE1_GFCLK_900000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_EVE2_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_EVE2_GFCLK_freqList[] =
{
    {535000000U, &PMHAL_PRCM_CLK_EVE2_GFCLK_535000000},
    {650000000U, &PMHAL_PRCM_CLK_EVE2_GFCLK_650000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_GMAC_RFT_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_GMAC_RFT_CLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_GMAC_RFT_CLK_266000000},
    {451584000U, &PMHAL_PRCM_CLK_GMAC_RFT_CLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_GMAC_MAIN_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_GMAC_MAIN_CLK_freqList[] =
{
    {125000000U, &PMHAL_PRCM_CLK_GMAC_MAIN_CLK_125000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_GMII_250MHZ_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_GMII_250MHZ_CLK_freqList[] =
{
    {250000000U, &PMHAL_PRCM_CLK_GMII_250MHZ_CLK_250000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_RMII_50MHZ_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_RMII_50MHZ_CLK_freqList[] =
{
    {50000000U, &PMHAL_PRCM_CLK_RMII_50MHZ_CLK_50000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_RGMII_5MHZ_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_RGMII_5MHZ_CLK_freqList[] =
{
    {5000000U, &PMHAL_PRCM_CLK_RGMII_5MHZ_CLK_5000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_GPU_CORE_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_GPU_CORE_GCLK_freqList[] =
{
    {425600000U, &PMHAL_PRCM_CLK_GPU_CORE_GCLK_425600000},
    {500000000U, &PMHAL_PRCM_CLK_GPU_CORE_GCLK_500000000},
    {532000000U, &PMHAL_PRCM_CLK_GPU_CORE_GCLK_532000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_GPU_HYD_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_GPU_HYD_GCLK_freqList[] =
{
    {425600000U, &PMHAL_PRCM_CLK_GPU_HYD_GCLK_425600000},
    {500000000U, &PMHAL_PRCM_CLK_GPU_HYD_GCLK_500000000},
    {532000000U, &PMHAL_PRCM_CLK_GPU_HYD_GCLK_532000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_IPU_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_IPU_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_IPU_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_IPU_96M_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_IPU_96M_GFCLK_freqList[] =
{
    {96000000U, &PMHAL_PRCM_CLK_IPU_96M_GFCLK_96000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP1_AHCLKR.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP1_AHCLKR_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP1_AHCLKR_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP1_AHCLKR_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP1_AHCLKR_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP1_AHCLKR_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP1_AHCLKR_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP1_AHCLKX.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP1_AHCLKX_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP1_AHCLKX_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP1_AHCLKX_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP1_AHCLKX_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP1_AHCLKX_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP1_AHCLKX_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_451584000},
    {225792000U, &PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_225792000},
    {112896000U, &PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_112896000},
    {56448000U, &PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER5_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER5_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER5_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER5_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER5_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER5_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER5_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER6_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER6_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER6_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER6_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER6_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER6_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER6_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER7_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER7_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER7_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER7_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER7_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER7_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER7_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER8_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER8_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER8_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER8_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER8_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER8_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER8_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART6_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART6_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART6_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART6_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_IPU1_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_IPU1_GFCLK_freqList[] =
{
    {212800000U, &PMHAL_PRCM_CLK_IPU1_GFCLK_212800000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_IPU2_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_IPU2_GFCLK_freqList[] =
{
    {212800000U, &PMHAL_PRCM_CLK_IPU2_GFCLK_212800000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_IVA_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_IVA_GCLK_freqList[] =
{
    {388333333U, &PMHAL_PRCM_CLK_IVA_GCLK_388333333},
    {430000000U, &PMHAL_PRCM_CLK_IVA_GCLK_430000000},
    {532000000U, &PMHAL_PRCM_CLK_IVA_GCLK_532000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INIT_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INIT_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_L3INIT_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INIT_L4_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INIT_L4_GICLK_freqList[] =
{
    {133000000U, &PMHAL_PRCM_CLK_L3INIT_L4_GICLK_133000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MMC1_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MMC1_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_MMC1_GFCLK_192000000},
    {96000000U, &PMHAL_PRCM_CLK_MMC1_GFCLK_96000000},
    {48000000U, &PMHAL_PRCM_CLK_MMC1_GFCLK_48000000},
    {128000000U, &PMHAL_PRCM_CLK_MMC1_GFCLK_128000000},
    {64000000U, &PMHAL_PRCM_CLK_MMC1_GFCLK_64000000},
    {32000000U, &PMHAL_PRCM_CLK_MMC1_GFCLK_32000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INIT_32K_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INIT_32K_GFCLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_L3INIT_32K_GFCLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MMC2_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MMC2_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_MMC2_GFCLK_192000000},
    {96000000U, &PMHAL_PRCM_CLK_MMC2_GFCLK_96000000},
    {48000000U, &PMHAL_PRCM_CLK_MMC2_GFCLK_48000000},
    {128000000U, &PMHAL_PRCM_CLK_MMC2_GFCLK_128000000},
    {64000000U, &PMHAL_PRCM_CLK_MMC2_GFCLK_64000000},
    {32000000U, &PMHAL_PRCM_CLK_MMC2_GFCLK_32000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INIT_48M_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INIT_48M_GFCLK_freqList[] =
{
    {48000000U, &PMHAL_PRCM_CLK_L3INIT_48M_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_SATA_REF_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_SATA_REF_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_SATA_REF_GFCLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INIT_960M_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INIT_960M_GFCLK_freqList[] =
{
    {960000000U, &PMHAL_PRCM_CLK_L3INIT_960M_GFCLK_960000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INSTR_TS_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_freqList[] =
{
    {2500000U, &PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_2500000},
    {1250000U, &PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1250000},
    {625000U, &PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_625000},
    {7056000U, &PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_7056000},
    {3528000U, &PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_3528000},
    {1764000U, &PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_1764000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_freqList[] =
{
    {2500000U, &PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_2500000},
    {1250000U, &PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1250000},
    {625000U, &PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_625000},
    {7056000U, &PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_7056000},
    {3528000U, &PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_3528000},
    {1764000U, &PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_1764000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3INSTR_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3INSTR_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_L3INSTR_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK_freqList[] =
{
    {133000000U, &PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK_133000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4CFG_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4CFG_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_L4CFG_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4CFG_L4_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4CFG_L4_GICLK_freqList[] =
{
    {133000000U, &PMHAL_PRCM_CLK_L4CFG_L4_GICLK_133000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4PER_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4PER_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_L4PER_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PER_96M_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PER_96M_GFCLK_freqList[] =
{
    {96000000U, &PMHAL_PRCM_CLK_PER_96M_GFCLK_96000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4PER_L4_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4PER_L4_GICLK_freqList[] =
{
    {133000000U, &PMHAL_PRCM_CLK_L4PER_L4_GICLK_133000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER10_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER10_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER10_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER10_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER10_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER10_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER10_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER11_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER11_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER11_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER11_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER11_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER11_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER11_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER2_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER2_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER2_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER2_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER2_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER2_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER2_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER3_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER3_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER3_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER3_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER3_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER3_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER3_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER4_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER4_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER4_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER4_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER4_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER4_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER4_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER9_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER9_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER9_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER9_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER9_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER9_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER9_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PER_12M_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PER_12M_GFCLK_freqList[] =
{
    {12000000U, &PMHAL_PRCM_CLK_PER_12M_GFCLK_12000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PER_48M_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PER_48M_GFCLK_freqList[] =
{
    {48000000U, &PMHAL_PRCM_CLK_PER_48M_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART1_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART1_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART1_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART1_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART2_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART2_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART2_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART2_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART3_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART3_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART3_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART3_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART4_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART4_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART4_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART4_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART5_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART5_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART5_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART5_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_GPIO_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_GPIO_GFCLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_GPIO_GFCLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4PER_32K_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4PER_32K_GFCLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_L4PER_32K_GFCLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MMC3_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MMC3_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_MMC3_GFCLK_192000000},
    {96000000U, &PMHAL_PRCM_CLK_MMC3_GFCLK_96000000},
    {48000000U, &PMHAL_PRCM_CLK_MMC3_GFCLK_48000000},
    {24000000U, &PMHAL_PRCM_CLK_MMC3_GFCLK_24000000},
    {12000000U, &PMHAL_PRCM_CLK_MMC3_GFCLK_12000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MMC4_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MMC4_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_MMC4_GFCLK_192000000},
    {96000000U, &PMHAL_PRCM_CLK_MMC4_GFCLK_96000000},
    {48000000U, &PMHAL_PRCM_CLK_MMC4_GFCLK_48000000},
    {24000000U, &PMHAL_PRCM_CLK_MMC4_GFCLK_24000000},
    {12000000U, &PMHAL_PRCM_CLK_MMC4_GFCLK_12000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_DCAN2_SYS_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_DCAN2_SYS_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_DCAN2_SYS_CLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4PER2_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4PER2_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_L4PER2_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART7_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART7_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART7_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART7_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART8_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART8_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART8_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART8_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART9_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART9_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART9_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART9_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_ICSS_IEP_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_ICSS_IEP_CLK_freqList[] =
{
    {200000000U, &PMHAL_PRCM_CLK_ICSS_IEP_CLK_200000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_ICSS_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_ICSS_CLK_freqList[] =
{
    {200000000U, &PMHAL_PRCM_CLK_ICSS_CLK_200000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PER_192M_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PER_192M_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_PER_192M_GFCLK_192000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP2_AHCLKX.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP2_AHCLKX_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP2_AHCLKX_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP2_AHCLKX_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP2_AHCLKX_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP2_AHCLKX_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP2_AHCLKX_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP2_AHCLKR.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP2_AHCLKR_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP2_AHCLKR_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP2_AHCLKR_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP2_AHCLKR_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP2_AHCLKR_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP2_AHCLKR_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_451584000},
    {225792000U, &PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_225792000},
    {112896000U, &PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_112896000},
    {56448000U, &PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP3_AHCLKX.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP3_AHCLKX_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP3_AHCLKX_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP3_AHCLKX_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP3_AHCLKX_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP3_AHCLKX_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP3_AHCLKX_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_451584000},
    {225792000U, &PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_225792000},
    {112896000U, &PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_112896000},
    {56448000U, &PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP4_AHCLKX.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP4_AHCLKX_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP4_AHCLKX_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP4_AHCLKX_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP4_AHCLKX_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP4_AHCLKX_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP4_AHCLKX_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_451584000},
    {225792000U, &PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_225792000},
    {112896000U, &PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_112896000},
    {56448000U, &PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP5_AHCLKX.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP5_AHCLKX_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP5_AHCLKX_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP5_AHCLKX_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP5_AHCLKX_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP5_AHCLKX_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP5_AHCLKX_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_451584000},
    {225792000U, &PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_225792000},
    {112896000U, &PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_112896000},
    {56448000U, &PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP6_AHCLKX.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP6_AHCLKX_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP6_AHCLKX_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP6_AHCLKX_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP6_AHCLKX_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP6_AHCLKX_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP6_AHCLKX_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_451584000},
    {225792000U, &PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_225792000},
    {112896000U, &PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_112896000},
    {56448000U, &PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP7_AHCLKX.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP7_AHCLKX_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP7_AHCLKX_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP7_AHCLKX_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP7_AHCLKX_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP7_AHCLKX_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP7_AHCLKX_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_451584000},
    {225792000U, &PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_225792000},
    {112896000U, &PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_112896000},
    {56448000U, &PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP8_AHCLKX.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP8_AHCLKX_freqList[] =
{
    {56448000U, &PMHAL_PRCM_CLK_MCASP8_AHCLKX_56448000},
    {20000000U, &PMHAL_PRCM_CLK_MCASP8_AHCLKX_20000000},
    {10000000U, &PMHAL_PRCM_CLK_MCASP8_AHCLKX_10000000},
    {24000000U, &PMHAL_PRCM_CLK_MCASP8_AHCLKX_24000000},
    {22579200U, &PMHAL_PRCM_CLK_MCASP8_AHCLKX_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_freqList[] =
{
    {451584000U, &PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_451584000},
    {225792000U, &PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_225792000},
    {112896000U, &PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_112896000},
    {56448000U, &PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_QSPI_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_QSPI_GFCLK_freqList[] =
{
    {128000000U, &PMHAL_PRCM_CLK_QSPI_GFCLK_128000000},
    {64000000U, &PMHAL_PRCM_CLK_QSPI_GFCLK_64000000},
    {32000000U, &PMHAL_PRCM_CLK_QSPI_GFCLK_32000000},
    {192000000U, &PMHAL_PRCM_CLK_QSPI_GFCLK_192000000},
    {96000000U, &PMHAL_PRCM_CLK_QSPI_GFCLK_96000000},
    {48000000U, &PMHAL_PRCM_CLK_QSPI_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4PER3_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4PER3_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_L4PER3_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4PER3_L4_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4PER3_L4_GICLK_freqList[] =
{
    {133000000U, &PMHAL_PRCM_CLK_L4PER3_L4_GICLK_133000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER13_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER13_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER13_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER13_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER13_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER13_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER13_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER14_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER14_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER14_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER14_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER14_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER14_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER14_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER15_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER15_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER15_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER15_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER15_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER15_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER15_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER16_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER16_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER16_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER16_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER16_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER16_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER16_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4SEC_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4SEC_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_L4SEC_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_L4SEC_L4_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_L4SEC_L4_GICLK_freqList[] =
{
    {133000000U, &PMHAL_PRCM_CLK_L4SEC_L4_GICLK_133000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MPU_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MPU_GCLK_freqList[] =
{
    {500000000U, &PMHAL_PRCM_CLK_MPU_GCLK_500000000},
    {750000000U, &PMHAL_PRCM_CLK_MPU_GCLK_750000000},
    {1000000000U, &PMHAL_PRCM_CLK_MPU_GCLK_1000000000},
    {1176000000U, &PMHAL_PRCM_CLK_MPU_GCLK_1176000000},
    {1500000000U, &PMHAL_PRCM_CLK_MPU_GCLK_1500000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PCIE_32K_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PCIE_32K_GFCLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_PCIE_32K_GFCLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PCIE_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PCIE_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_PCIE_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PCIE_PHY_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PCIE_PHY_GCLK_freqList[] =
{
    {0U, &PMHAL_PRCM_CLK_PCIE_PHY_GCLK_0}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK_freqList[] =
{
    {0U, &PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK_0}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PCIE_REF_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PCIE_REF_GFCLK_freqList[] =
{
    {34322580U, &PMHAL_PRCM_CLK_PCIE_REF_GFCLK_34322580}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_PCIE_SYS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_PCIE_SYS_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_PCIE_SYS_GFCLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_RTC_L4_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_RTC_L4_GICLK_freqList[] =
{
    {133000000U, &PMHAL_PRCM_CLK_RTC_L4_GICLK_133000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_RTC_AUX_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_RTC_AUX_CLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_RTC_AUX_CLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_VIP1_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_VIP1_GCLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_VIP1_GCLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_VIP2_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_VIP2_GCLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_VIP2_GCLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_VIP3_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_VIP3_GCLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_VIP3_GCLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_VPE_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_VPE_GCLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_VPE_GCLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_EMU_SYS_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_EMU_SYS_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_EMU_SYS_CLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_ADC_L3_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_ADC_L3_GICLK_freqList[] =
{
    {266000000U, &PMHAL_PRCM_CLK_ADC_L3_GICLK_266000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_FUNC_32K_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_FUNC_32K_CLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_FUNC_32K_CLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_WKUPAON_GICLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_WKUPAON_GICLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_WKUPAON_GICLK_20000000},
    {56448000U, &PMHAL_PRCM_CLK_WKUPAON_GICLK_56448000},
    {28224000U, &PMHAL_PRCM_CLK_WKUPAON_GICLK_28224000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_DCAN1_SYS_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_DCAN1_SYS_CLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_DCAN1_SYS_CLK_20000000},
    {22579200U, &PMHAL_PRCM_CLK_DCAN1_SYS_CLK_22579200}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK_freqList[] =
{
    {32786U, &PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK_32786}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK_20000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_TIMER1_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_TIMER1_GFCLK_freqList[] =
{
    {20000000U, &PMHAL_PRCM_CLK_TIMER1_GFCLK_20000000},
    {10000000U, &PMHAL_PRCM_CLK_TIMER1_GFCLK_10000000},
    {32786U, &PMHAL_PRCM_CLK_TIMER1_GFCLK_32786},
    {22579200U, &PMHAL_PRCM_CLK_TIMER1_GFCLK_22579200},
    {451584000U, &PMHAL_PRCM_CLK_TIMER1_GFCLK_451584000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_SECURE_32K_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_SECURE_32K_CLK_freqList[] =
{
    {0U, &PMHAL_PRCM_CLK_SECURE_32K_CLK_0}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_UART10_GFCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_UART10_GFCLK_freqList[] =
{
    {192000000U, &PMHAL_PRCM_CLK_UART10_GFCLK_192000000},
    {48000000U, &PMHAL_PRCM_CLK_UART10_GFCLK_48000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_ISS_GCLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_ISS_GCLK_freqList[] =
{
    {355000000U, &PMHAL_PRCM_CLK_ISS_GCLK_355000000},
    {425600000U, &PMHAL_PRCM_CLK_ISS_GCLK_425600000},
    {532000000U, &PMHAL_PRCM_CLK_ISS_GCLK_532000000}
};
/**
 * \brief  List of the frequencies and pointer to configuration
 *         structures for the clock PMHAL_PRCM_CLK_MCAN_CLK.
 */
pmlibClockRateFreqList_t PMHAL_PRCM_CLK_MCAN_CLK_freqList[] =
{
    {80000000U, &PMHAL_PRCM_CLK_MCAN_CLK_80000000}
};
/* -------------------------------------------------------------------------- */
/*              Clock ID to Frequency List Array                              */
/* -------------------------------------------------------------------------- */

/**
 * \brief  Array containing the frequency list for all the clocks
 *         in the device.
 */
pmlibClockRateAllFreqList_t  pmlibClockRateAllClockFreq [] =
{
    {PMHAL_PRCM_CLK_ATL_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ATL_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_ATL_L3_GICLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_ATL_L4_GICLK */
    {PMHAL_PRCM_CLK_ATL_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ATL_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_ATL_GFCLK */
    {PMHAL_PRCM_CLK_ABE_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ABE_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_ABE_GICLK */
    {PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_CLKOUTMUX1_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_CLKOUTMUX1_CLK */
    {PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_CLKOUTMUX2_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_CLKOUTMUX2_CLK */
    {PMHAL_PRCM_CLK_L3INIT_60M_FCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_60M_FCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INIT_60M_FCLK */
    {PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_COREAON_L4_GICLK */
    {PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK */
    {PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK */
    {PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK */
    {PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK */
    {PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK */
    {PMHAL_PRCM_CLK_COREAON_32K_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_COREAON_32K_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_COREAON_32K_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_CUSTEFUSE_L4_GICLK */
    {PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK */
    {PMHAL_PRCM_CLK_DMA_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DMA_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_DMA_L3_GICLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_DMA_L4_GICLK */
    {PMHAL_PRCM_CLK_DSP1_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DSP1_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_DSP1_GFCLK */
    {PMHAL_PRCM_CLK_DSP2_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DSP2_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_DSP2_GFCLK */
    {PMHAL_PRCM_CLK_BB2D_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_BB2D_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_BB2D_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_DSS_L3_GICLK */
    {PMHAL_PRCM_CLK_HDMI_CEC_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_HDMI_CEC_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_HDMI_CEC_GFCLK */
    {PMHAL_PRCM_CLK_HDMI_PHY_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_HDMI_PHY_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_HDMI_PHY_GFCLK */
    {PMHAL_PRCM_CLK_DSS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DSS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_DSS_GFCLK */
    {PMHAL_PRCM_CLK_HDMI_DPLL_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_HDMI_DPLL_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_HDMI_DPLL_CLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_DSS_L4_GICLK */
    {PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK */
    {PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK */
    {PMHAL_PRCM_CLK_SDVENC_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SDVENC_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_SDVENC_GFCLK */
    {PMHAL_PRCM_CLK_EMIF_DLL_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EMIF_DLL_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_EMIF_DLL_GCLK */
    {PMHAL_PRCM_CLK_EMIF_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EMIF_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_EMIF_L3_GICLK */
    {PMHAL_PRCM_CLK_EMIF_PHY_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EMIF_PHY_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_EMIF_PHY_GCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_EMIF_L4_GICLK */
    {PMHAL_PRCM_CLK_EVE1_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EVE1_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_EVE1_GFCLK */
    {PMHAL_PRCM_CLK_EVE2_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EVE2_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_EVE2_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_EVE3_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_EVE4_GFCLK */
    {PMHAL_PRCM_CLK_GMAC_RFT_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GMAC_RFT_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_GMAC_RFT_CLK */
    {PMHAL_PRCM_CLK_GMAC_MAIN_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GMAC_MAIN_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_GMAC_MAIN_CLK */
    {PMHAL_PRCM_CLK_GMII_250MHZ_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GMII_250MHZ_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_GMII_250MHZ_CLK */
    {PMHAL_PRCM_CLK_RMII_50MHZ_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_RMII_50MHZ_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_RMII_50MHZ_CLK */
    {PMHAL_PRCM_CLK_RGMII_5MHZ_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_RGMII_5MHZ_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_RGMII_5MHZ_CLK */
    {PMHAL_PRCM_CLK_GPU_CORE_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPU_CORE_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_GPU_CORE_GCLK */
    {PMHAL_PRCM_CLK_GPU_HYD_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPU_HYD_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_GPU_HYD_GCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_GPU_L3_GICLK */
    {PMHAL_PRCM_CLK_IPU_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_IPU_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_IPU_L3_GICLK */
    {PMHAL_PRCM_CLK_IPU_96M_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_IPU_96M_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_IPU_96M_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_IPU_L4_GICLK */
    {PMHAL_PRCM_CLK_MCASP1_AHCLKR_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKR_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP1_AHCLKR */
    {PMHAL_PRCM_CLK_MCASP1_AHCLKX_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AHCLKX_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP1_AHCLKX */
    {PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK */
    {PMHAL_PRCM_CLK_TIMER5_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER5_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER5_GFCLK */
    {PMHAL_PRCM_CLK_TIMER6_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER6_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER6_GFCLK */
    {PMHAL_PRCM_CLK_TIMER7_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER7_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER7_GFCLK */
    {PMHAL_PRCM_CLK_TIMER8_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER8_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER8_GFCLK */
    {PMHAL_PRCM_CLK_UART6_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART6_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART6_GFCLK */
    {PMHAL_PRCM_CLK_IPU1_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_IPU1_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_IPU1_GFCLK */
    {PMHAL_PRCM_CLK_IPU2_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_IPU2_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_IPU2_GFCLK */
    {PMHAL_PRCM_CLK_IVA_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_IVA_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_IVA_GCLK */
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INIT_L3_GICLK */
    {PMHAL_PRCM_CLK_L3INIT_L4_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_L4_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INIT_L4_GICLK */
    {PMHAL_PRCM_CLK_MMC1_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC1_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MMC1_GFCLK */
    {PMHAL_PRCM_CLK_L3INIT_32K_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_32K_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INIT_32K_GFCLK */
    {PMHAL_PRCM_CLK_MMC2_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC2_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MMC2_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_MLB_SHB_L3_GICLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_MLB_SPB_L4_GICLK */
    {PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK */
    {PMHAL_PRCM_CLK_L3INIT_48M_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_48M_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INIT_48M_GFCLK */
    {PMHAL_PRCM_CLK_SATA_REF_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SATA_REF_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_SATA_REF_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_USB_LFPS_TX_GFCLK */
    {PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK */
    {PMHAL_PRCM_CLK_L3INIT_960M_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INIT_960M_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INIT_960M_GFCLK */
    {PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_TS_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INSTR_TS_GCLK */
    {PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK */
    {PMHAL_PRCM_CLK_L3INSTR_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3INSTR_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3INSTR_L3_GICLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_L3INSTR_L4_GICLK */
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK */
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK */
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4CFG_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4CFG_L3_GICLK */
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4CFG_L4_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4CFG_L4_GICLK */
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4PER_L3_GICLK */
    {PMHAL_PRCM_CLK_PER_96M_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PER_96M_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PER_96M_GFCLK */
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER_L4_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4PER_L4_GICLK */
    {PMHAL_PRCM_CLK_TIMER10_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER10_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER10_GFCLK */
    {PMHAL_PRCM_CLK_TIMER11_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER11_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER11_GFCLK */
    {PMHAL_PRCM_CLK_TIMER2_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER2_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER2_GFCLK */
    {PMHAL_PRCM_CLK_TIMER3_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER3_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER3_GFCLK */
    {PMHAL_PRCM_CLK_TIMER4_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER4_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER4_GFCLK */
    {PMHAL_PRCM_CLK_TIMER9_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER9_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER9_GFCLK */
    {PMHAL_PRCM_CLK_PER_12M_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PER_12M_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PER_12M_GFCLK */
    {PMHAL_PRCM_CLK_PER_48M_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PER_48M_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PER_48M_GFCLK */
    {PMHAL_PRCM_CLK_UART1_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART1_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART1_GFCLK */
    {PMHAL_PRCM_CLK_UART2_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART2_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART2_GFCLK */
    {PMHAL_PRCM_CLK_UART3_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART3_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART3_GFCLK */
    {PMHAL_PRCM_CLK_UART4_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART4_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART4_GFCLK */
    {PMHAL_PRCM_CLK_UART5_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART5_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART5_GFCLK */
    {PMHAL_PRCM_CLK_GPIO_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_GPIO_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_GPIO_GFCLK */
    {PMHAL_PRCM_CLK_L4PER_32K_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER_32K_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4PER_32K_GFCLK */
    {PMHAL_PRCM_CLK_MMC3_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC3_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MMC3_GFCLK */
    {PMHAL_PRCM_CLK_MMC4_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MMC4_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MMC4_GFCLK */
    {PMHAL_PRCM_CLK_DCAN2_SYS_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DCAN2_SYS_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_DCAN2_SYS_CLK */
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER2_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4PER2_L3_GICLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_L4PER2_L4_GICLK */
    {PMHAL_PRCM_CLK_UART7_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART7_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART7_GFCLK */
    {PMHAL_PRCM_CLK_UART8_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART8_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART8_GFCLK */
    {PMHAL_PRCM_CLK_UART9_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART9_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART9_GFCLK */
    {PMHAL_PRCM_CLK_ICSS_IEP_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ICSS_IEP_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_ICSS_IEP_CLK */
    {PMHAL_PRCM_CLK_ICSS_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ICSS_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_ICSS_CLK */
    {PMHAL_PRCM_CLK_PER_192M_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PER_192M_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PER_192M_GFCLK */
    {PMHAL_PRCM_CLK_MCASP2_AHCLKX_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKX_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP2_AHCLKX */
    {PMHAL_PRCM_CLK_MCASP2_AHCLKR_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AHCLKR_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP2_AHCLKR */
    {PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK */
    {PMHAL_PRCM_CLK_MCASP3_AHCLKX_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AHCLKX_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP3_AHCLKX */
    {PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK */
    {PMHAL_PRCM_CLK_MCASP4_AHCLKX_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AHCLKX_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP4_AHCLKX */
    {PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP4_AUX_GFCLK */
    {PMHAL_PRCM_CLK_MCASP5_AHCLKX_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AHCLKX_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP5_AHCLKX */
    {PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP5_AUX_GFCLK */
    {PMHAL_PRCM_CLK_MCASP6_AHCLKX_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AHCLKX_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP6_AHCLKX */
    {PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP6_AUX_GFCLK */
    {PMHAL_PRCM_CLK_MCASP7_AHCLKX_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AHCLKX_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP7_AHCLKX */
    {PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP7_AUX_GFCLK */
    {PMHAL_PRCM_CLK_MCASP8_AHCLKX_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AHCLKX_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP8_AHCLKX */
    {PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCASP8_AUX_GFCLK */
    {PMHAL_PRCM_CLK_QSPI_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_QSPI_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_QSPI_GFCLK */
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER3_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4PER3_L3_GICLK */
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4PER3_L4_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4PER3_L4_GICLK */
    {PMHAL_PRCM_CLK_TIMER13_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER13_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER13_GFCLK */
    {PMHAL_PRCM_CLK_TIMER14_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER14_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER14_GFCLK */
    {PMHAL_PRCM_CLK_TIMER15_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER15_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER15_GFCLK */
    {PMHAL_PRCM_CLK_TIMER16_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER16_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER16_GFCLK */
    {PMHAL_PRCM_CLK_L4SEC_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4SEC_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4SEC_L3_GICLK */
    {PMHAL_PRCM_CLK_L4SEC_L4_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_L4SEC_L4_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_L4SEC_L4_GICLK */
    {PMHAL_PRCM_CLK_MPU_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MPU_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MPU_GCLK */
    {PMHAL_PRCM_CLK_PCIE_32K_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PCIE_32K_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PCIE_32K_GFCLK */
    {PMHAL_PRCM_CLK_PCIE_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PCIE_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PCIE_L3_GICLK */
    {PMHAL_PRCM_CLK_PCIE_PHY_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PCIE_PHY_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PCIE_PHY_GCLK */
    {PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PCIE_PHY_DIV_GCLK */
    {PMHAL_PRCM_CLK_PCIE_REF_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PCIE_REF_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PCIE_REF_GFCLK */
    {PMHAL_PRCM_CLK_PCIE_SYS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_PCIE_SYS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_PCIE_SYS_GFCLK */
    {PMHAL_PRCM_CLK_RTC_L4_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_RTC_L4_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_RTC_L4_GICLK */
    {PMHAL_PRCM_CLK_RTC_AUX_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_RTC_AUX_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_RTC_AUX_CLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_LVDSRX_96M_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_LVDSRX_L4_GICLK */
    {PMHAL_PRCM_CLK_VIP1_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP1_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_VIP1_GCLK */
    {PMHAL_PRCM_CLK_VIP2_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP2_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_VIP2_GCLK */
    {PMHAL_PRCM_CLK_VIP3_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VIP3_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_VIP3_GCLK */
    {PMHAL_PRCM_CLK_VPE_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_VPE_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_VPE_GCLK */
    {PMHAL_PRCM_CLK_EMU_SYS_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_EMU_SYS_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_EMU_SYS_CLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_ADC_GFCLK */
    {PMHAL_PRCM_CLK_ADC_L3_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ADC_L3_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_ADC_L3_GICLK */
    {PMHAL_PRCM_CLK_FUNC_32K_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_FUNC_32K_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_FUNC_32K_CLK */
    {PMHAL_PRCM_CLK_WKUPAON_GICLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_GICLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_WKUPAON_GICLK */
    {PMHAL_PRCM_CLK_DCAN1_SYS_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_DCAN1_SYS_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_DCAN1_SYS_CLK */
    {PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK */
    {PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK */
    {PMHAL_PRCM_CLK_TIMER1_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_TIMER1_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_TIMER1_GFCLK */
    {PMHAL_PRCM_CLK_SECURE_32K_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_SECURE_32K_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_SECURE_32K_CLK */
    {PMHAL_PRCM_CLK_UART10_GFCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_UART10_GFCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_UART10_GFCLK */
    {NULL, 0U},
    /**< PMHAL_PRCM_CLK_RTC_32K_GFCLK */
    {PMHAL_PRCM_CLK_ISS_GCLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_ISS_GCLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_ISS_GCLK */
    {PMHAL_PRCM_CLK_MCAN_CLK_freqList,
     PM_UTIL_VSIZE_TYPE(
        PMHAL_PRCM_CLK_MCAN_CLK_freqList,
        pmlibClockRateFreqList_t)},
    /**< PMHAL_PRCM_CLK_MCAN_CLK */
};

/* -------------------------------------------------------------------------- */
/*              Generic Clock ID List                                         */
/* -------------------------------------------------------------------------- */
/**
 * \brief  Array containing the mapping for which clock of the module can
 *         be referred to by PMHAL_PRCM_CLK_GENERIC in the Set and Get API.
 */
pmhalPrcmClockId_t gModuleGenericClkList[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    PMHAL_PRCM_CLK_ATL_GFCLK,
    /**< PMHAL_PRCM_MOD_ATL */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4
    PMHAL_PRCM_CLK_ABE_GICLK,
    /**< PMHAL_PRCM_MOD_DUMMY_MODULE4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1
    PMHAL_PRCM_CLK_CLKOUTMUX1_CLK,
    /**< PMHAL_PRCM_MOD_DUMMY_MODULE1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2
    PMHAL_PRCM_CLK_CLKOUTMUX2_CLK,
    /**< PMHAL_PRCM_MOD_DUMMY_MODULE2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3
    PMHAL_PRCM_CLK_L3INIT_60M_FCLK,
    /**< PMHAL_PRCM_MOD_DUMMY_MODULE3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DUMMY_MODULE3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE
    PMHAL_PRCM_CLK_COREAON_IO_SRCOMP_GFCLK,
    /**< PMHAL_PRCM_MOD_IO_SRCOMP_CORE */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
    PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
    PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU
    PMHAL_PRCM_CLK_SR_GPU_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_SMARTREFLEX_GPU */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD
    PMHAL_PRCM_CLK_SR_IVAHD_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_IVAHD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU
    PMHAL_PRCM_CLK_SR_MPU_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_SMARTREFLEX_MPU */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON
    PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
    /**< PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY1_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON
    PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
    /**< PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY2_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON
    PMHAL_PRCM_CLK_COREAON_32K_GFCLK,
    /**< PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_PHY3_ALWAYS_ON */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM
    PMHAL_PRCM_CLK_DMA_L3_GICLK,
    /**< PMHAL_PRCM_MOD_DMA_SYSTEM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_SYSTEM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    PMHAL_PRCM_CLK_DSP1_GFCLK,
    /**< PMHAL_PRCM_MOD_DSP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    PMHAL_PRCM_CLK_DSP2_GFCLK,
    /**< PMHAL_PRCM_MOD_DSP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_BB2D
    PMHAL_PRCM_CLK_BB2D_GFCLK,
    /**< PMHAL_PRCM_MOD_BB2D */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_BB2D */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    PMHAL_PRCM_CLK_DSS_GFCLK,
    /**< PMHAL_PRCM_MOD_DSS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SDVENC
    PMHAL_PRCM_CLK_SDVENC_GFCLK,
    /**< PMHAL_PRCM_MOD_SDVENC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SDVENC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
    PMHAL_PRCM_CLK_EMIF_DLL_GCLK,
    /**< PMHAL_PRCM_MOD_DLL */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMM
    PMHAL_PRCM_CLK_EMIF_L3_GICLK,
    /**< PMHAL_PRCM_MOD_DMM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    PMHAL_PRCM_CLK_EMIF_PHY_GCLK,
    /**< PMHAL_PRCM_MOD_EMIF1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF2
    PMHAL_PRCM_CLK_EMIF_PHY_GCLK,
    /**< PMHAL_PRCM_MOD_EMIF2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW
    PMHAL_PRCM_CLK_EMIF_L3_GICLK,
    /**< PMHAL_PRCM_MOD_EMIF_OCP_FW */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF_OCP_FW */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    PMHAL_PRCM_CLK_EVE1_GFCLK,
    /**< PMHAL_PRCM_MOD_EVE1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE2
    PMHAL_PRCM_CLK_EVE2_GFCLK,
    /**< PMHAL_PRCM_MOD_EVE2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    PMHAL_PRCM_CLK_GMAC_MAIN_CLK,
    /**< PMHAL_PRCM_MOD_CPGMAC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPU
    PMHAL_PRCM_CLK_GPU_CORE_GCLK,
    /**< PMHAL_PRCM_MOD_GPU */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C5
    PMHAL_PRCM_CLK_IPU_96M_GFCLK,
    /**< PMHAL_PRCM_MOD_I2C5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    PMHAL_PRCM_CLK_MCASP1_AHCLKR,
    /**< PMHAL_PRCM_MOD_MCASP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
    PMHAL_PRCM_CLK_TIMER5_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
    PMHAL_PRCM_CLK_TIMER6_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
    PMHAL_PRCM_CLK_TIMER7_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
    PMHAL_PRCM_CLK_TIMER8_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART6
    PMHAL_PRCM_CLK_UART6_GFCLK,
    /**< PMHAL_PRCM_MOD_UART6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
    PMHAL_PRCM_CLK_IPU1_GFCLK,
    /**< PMHAL_PRCM_MOD_IPU1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU2
    PMHAL_PRCM_CLK_IPU2_GFCLK,
    /**< PMHAL_PRCM_MOD_IPU2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IVA
    PMHAL_PRCM_CLK_IVA_GCLK,
    /**< PMHAL_PRCM_MOD_IVA */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IVA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SL2
    PMHAL_PRCM_CLK_IVA_GCLK,
    /**< PMHAL_PRCM_MOD_SL2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
    /**< PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC1
    PMHAL_PRCM_CLK_MMC1_GFCLK,
    /**< PMHAL_PRCM_MOD_MMC1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC2
    PMHAL_PRCM_CLK_MMC2_GFCLK,
    /**< PMHAL_PRCM_MOD_MMC2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MLB_SS
    PMHAL_PRCM_CLK_MLB_SYS_L3_GFCLK,
    /**< PMHAL_PRCM_MOD_MLB_SS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MLB_SS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SATA
    PMHAL_PRCM_CLK_L3INIT_48M_GFCLK,
    /**< PMHAL_PRCM_MOD_SATA */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SATA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1
    PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
    /**< PMHAL_PRCM_MOD_OCP2SCP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3
    PMHAL_PRCM_CLK_L3INIT_L4_GICLK,
    /**< PMHAL_PRCM_MOD_OCP2SCP3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1
    PMHAL_PRCM_CLK_L3INIT_960M_GFCLK,
    /**< PMHAL_PRCM_MOD_USB_OTG_SS1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2
    PMHAL_PRCM_CLK_L3INIT_960M_GFCLK,
    /**< PMHAL_PRCM_MOD_USB_OTG_SS2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3
    PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
    /**< PMHAL_PRCM_MOD_USB_OTG_SS3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4
    PMHAL_PRCM_CLK_USB_OTG_SS_REF_CLK,
    /**< PMHAL_PRCM_MOD_USB_OTG_SS4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_USB_OTG_SS4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
    PMHAL_PRCM_CLK_L3INSTR_TS_GCLK,
    /**< PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
    PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK,
    /**< PMHAL_PRCM_MOD_DLL_AGING */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
    PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
    /**< PMHAL_PRCM_MOD_L3_INSTR */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
    PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
    /**< PMHAL_PRCM_MOD_L3_MAIN_2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
    PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
    /**< PMHAL_PRCM_MOD_OCP_WP_NOC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_GPMC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_L3_MAIN_1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MMU_EDMA */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MMU_PCIESS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_PCIESS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_OCMC_RAM1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_OCMC_RAM2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_OCMC_RAM3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_OCMC_ROM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_IVA2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_IVA2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP1
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_VCP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VCP2
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_VCP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_CME */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_CME */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_HDMI */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_HDMI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_ICM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_ICM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_SATA2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SATA2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_UNKNOWN4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_UNKNOWN5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_UNKNOWN6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_VIDEOPLL1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_VIDEOPLL2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3
    PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_VIDEOPLL3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_VIDEOPLL3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPCC
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_TPCC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPCC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_TPTC1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
    PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
    /**< PMHAL_PRCM_MOD_TPTC2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_L4_CFG */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2
    PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
    /**< PMHAL_PRCM_MOD_OCP2SCP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP2SCP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_SAR_ROM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_ROM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC
    PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_RTC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM
    PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_SDRAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP
    PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SMARTREFLEX_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_SPINLOCK */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_IO_DELAY_BLOCK */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_DELAY_BLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX10 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX11 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX12 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX13 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9
    PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
    /**< PMHAL_PRCM_MOD_MAILBOX9 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    PMHAL_PRCM_CLK_PER_96M_GFCLK,
    /**< PMHAL_PRCM_MOD_I2C1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    PMHAL_PRCM_CLK_PER_96M_GFCLK,
    /**< PMHAL_PRCM_MOD_I2C2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C3
    PMHAL_PRCM_CLK_PER_96M_GFCLK,
    /**< PMHAL_PRCM_MOD_I2C3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C4
    PMHAL_PRCM_CLK_PER_96M_GFCLK,
    /**< PMHAL_PRCM_MOD_I2C4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
    /**< PMHAL_PRCM_MOD_L4_PER1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER10
    PMHAL_PRCM_CLK_TIMER10_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER10 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER11
    PMHAL_PRCM_CLK_TIMER11_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER11 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER11 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
    PMHAL_PRCM_CLK_TIMER2_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
    PMHAL_PRCM_CLK_TIMER3_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
    PMHAL_PRCM_CLK_TIMER4_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER9
    PMHAL_PRCM_CLK_TIMER9_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER9 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    PMHAL_PRCM_CLK_L4PER_L3_GICLK,
    /**< PMHAL_PRCM_MOD_ELM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_HDQ1W
    PMHAL_PRCM_CLK_PER_12M_GFCLK,
    /**< PMHAL_PRCM_MOD_HDQ1W */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_HDQ1W */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    PMHAL_PRCM_CLK_PER_48M_GFCLK,
    /**< PMHAL_PRCM_MOD_MCSPI1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    PMHAL_PRCM_CLK_PER_48M_GFCLK,
    /**< PMHAL_PRCM_MOD_MCSPI2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    PMHAL_PRCM_CLK_PER_48M_GFCLK,
    /**< PMHAL_PRCM_MOD_MCSPI3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    PMHAL_PRCM_CLK_PER_48M_GFCLK,
    /**< PMHAL_PRCM_MOD_MCSPI4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    PMHAL_PRCM_CLK_UART1_GFCLK,
    /**< PMHAL_PRCM_MOD_UART1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    PMHAL_PRCM_CLK_UART2_GFCLK,
    /**< PMHAL_PRCM_MOD_UART2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    PMHAL_PRCM_CLK_UART3_GFCLK,
    /**< PMHAL_PRCM_MOD_UART3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART4
    PMHAL_PRCM_CLK_UART4_GFCLK,
    /**< PMHAL_PRCM_MOD_UART4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART5
    PMHAL_PRCM_CLK_UART5_GFCLK,
    /**< PMHAL_PRCM_MOD_UART5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    PMHAL_PRCM_CLK_GPIO_GFCLK,
    /**< PMHAL_PRCM_MOD_GPIO2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    PMHAL_PRCM_CLK_GPIO_GFCLK,
    /**< PMHAL_PRCM_MOD_GPIO3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    PMHAL_PRCM_CLK_GPIO_GFCLK,
    /**< PMHAL_PRCM_MOD_GPIO4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO5
    PMHAL_PRCM_CLK_GPIO_GFCLK,
    /**< PMHAL_PRCM_MOD_GPIO5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO6
    PMHAL_PRCM_CLK_GPIO_GFCLK,
    /**< PMHAL_PRCM_MOD_GPIO6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO7
    PMHAL_PRCM_CLK_GPIO_GFCLK,
    /**< PMHAL_PRCM_MOD_GPIO7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO8
    PMHAL_PRCM_CLK_GPIO_GFCLK,
    /**< PMHAL_PRCM_MOD_GPIO8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC3
    PMHAL_PRCM_CLK_MMC3_GFCLK,
    /**< PMHAL_PRCM_MOD_MMC3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    PMHAL_PRCM_CLK_MMC4_GFCLK,
    /**< PMHAL_PRCM_MOD_MMC4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
    PMHAL_PRCM_CLK_DCAN2_SYS_CLK,
    /**< PMHAL_PRCM_MOD_DCAN2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
    PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
    /**< PMHAL_PRCM_MOD_L4_PER2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART7
    PMHAL_PRCM_CLK_UART7_GFCLK,
    /**< PMHAL_PRCM_MOD_UART7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART8
    PMHAL_PRCM_CLK_UART8_GFCLK,
    /**< PMHAL_PRCM_MOD_UART8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART9
    PMHAL_PRCM_CLK_UART9_GFCLK,
    /**< PMHAL_PRCM_MOD_UART9 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART9 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS1
    PMHAL_PRCM_CLK_ICSS_CLK,
    /**< PMHAL_PRCM_MOD_PRUSS1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PRUSS2
    PMHAL_PRCM_CLK_ICSS_CLK,
    /**< PMHAL_PRCM_MOD_PRUSS2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PRUSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    PMHAL_PRCM_CLK_MCASP2_AHCLKR,
    /**< PMHAL_PRCM_MOD_MCASP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    PMHAL_PRCM_CLK_MCASP3_AHCLKX,
    /**< PMHAL_PRCM_MOD_MCASP3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP4
    PMHAL_PRCM_CLK_MCASP4_AHCLKX,
    /**< PMHAL_PRCM_MOD_MCASP4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP5
    PMHAL_PRCM_CLK_MCASP5_AHCLKX,
    /**< PMHAL_PRCM_MOD_MCASP5 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP6
    PMHAL_PRCM_CLK_MCASP6_AHCLKX,
    /**< PMHAL_PRCM_MOD_MCASP6 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP7
    PMHAL_PRCM_CLK_MCASP7_AHCLKX,
    /**< PMHAL_PRCM_MOD_MCASP7 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP8
    PMHAL_PRCM_CLK_MCASP8_AHCLKX,
    /**< PMHAL_PRCM_MOD_MCASP8 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
    /**< PMHAL_PRCM_MOD_PWMSS1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS2
    PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
    /**< PMHAL_PRCM_MOD_PWMSS2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS3
    PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
    /**< PMHAL_PRCM_MOD_PWMSS3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    PMHAL_PRCM_CLK_QSPI_GFCLK,
    /**< PMHAL_PRCM_MOD_QSPI */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
    PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
    /**< PMHAL_PRCM_MOD_L4_PER3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER13
    PMHAL_PRCM_CLK_TIMER13_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER13 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER13 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER14
    PMHAL_PRCM_CLK_TIMER14_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER14 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER14 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER15
    PMHAL_PRCM_CLK_TIMER15_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER15 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER15 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER16
    PMHAL_PRCM_CLK_TIMER16_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER16 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER16 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES1
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
    /**< PMHAL_PRCM_MOD_AES1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_AES2
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
    /**< PMHAL_PRCM_MOD_AES2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_AES2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DES3DES
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
    /**< PMHAL_PRCM_MOD_DES3DES */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DES3DES */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
    /**< PMHAL_PRCM_MOD_DMA_CRYPTO */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DMA_CRYPTO */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_FPKA
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
    /**< PMHAL_PRCM_MOD_FPKA */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_FPKA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RNG
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
    /**< PMHAL_PRCM_MOD_RNG */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RNG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
    /**< PMHAL_PRCM_MOD_SHA2MD51 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD51 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52
    PMHAL_PRCM_CLK_L4SEC_L3_GICLK,
    /**< PMHAL_PRCM_MOD_SHA2MD52 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SHA2MD52 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU
    PMHAL_PRCM_CLK_MPU_GCLK,
    /**< PMHAL_PRCM_MOD_MPU */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG
    PMHAL_PRCM_CLK_MPU_GCLK,
    /**< PMHAL_PRCM_MOD_MPU_MPU_DBG */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_MPU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS1
    PMHAL_PRCM_CLK_PCIE_REF_GFCLK,
    /**< PMHAL_PRCM_MOD_PCIESS1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PCIESS2
    PMHAL_PRCM_CLK_PCIE_REF_GFCLK,
    /**< PMHAL_PRCM_MOD_PCIESS2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PCIESS2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTCSS
    PMHAL_PRCM_CLK_RTC_AUX_CLK,
    /**< PMHAL_PRCM_MOD_RTCSS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTCSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    PMHAL_PRCM_CLK_VIP1_GCLK,
    /**< PMHAL_PRCM_MOD_VIP1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP2
    PMHAL_PRCM_CLK_VIP2_GCLK,
    /**< PMHAL_PRCM_MOD_VIP2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VPE
    PMHAL_PRCM_CLK_VPE_GCLK,
    /**< PMHAL_PRCM_MOD_VPE */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VPE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    PMHAL_PRCM_CLK_EMU_SYS_CLK,
    /**< PMHAL_PRCM_MOD_DEBUG_LOGIC */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG
    PMHAL_PRCM_CLK_EMU_SYS_CLK,
    /**< PMHAL_PRCM_MOD_MPU_EMU_DBG */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MPU_EMU_DBG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    PMHAL_PRCM_CLK_FUNC_32K_CLK,
    /**< PMHAL_PRCM_MOD_COUNTER_32K */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
    PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
    /**< PMHAL_PRCM_MOD_DCAN1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_GPIO1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP
    PMHAL_PRCM_CLK_WKUPAON_IO_SRCOMP_GFCLK,
    /**< PMHAL_PRCM_MOD_IO_SRCOMP_WKUP */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IO_SRCOMP_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_KBD
    PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_KBD */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_KBD */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_L4_WKUP */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_SAR_RAM */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SAR_RAM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_SAFETY1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_SAFETY2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_SAFETY3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_SAFETY4 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_SAFETY4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_UNKNOWN2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3
    PMHAL_PRCM_CLK_WKUPAON_GICLK,
    /**< PMHAL_PRCM_MOD_SPARE_UNKNOWN3 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPARE_UNKNOWN3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    PMHAL_PRCM_CLK_TIMER1_GFCLK,
    /**< PMHAL_PRCM_MOD_TIMER1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER12
    PMHAL_PRCM_CLK_SECURE_32K_CLK,
    /**< PMHAL_PRCM_MOD_TIMER12 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER12 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART10
    PMHAL_PRCM_CLK_UART10_GFCLK,
    /**< PMHAL_PRCM_MOD_UART10 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART10 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1
    PMHAL_PRCM_CLK_SECURE_32K_CLK,
    /**< PMHAL_PRCM_MOD_WD_TIMER1 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2
    PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
    /**< PMHAL_PRCM_MOD_WD_TIMER2 */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_WD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
    PMHAL_PRCM_CLK_ISS_GCLK,
    /**< PMHAL_PRCM_MOD_ISS */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAL
    PMHAL_PRCM_CLK_VIP3_GCLK,
    /**< PMHAL_PRCM_MOD_CAL */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
    PMHAL_PRCM_CLK_MCAN_CLK,
    /**< PMHAL_PRCM_MOD_MCAN */
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
};

