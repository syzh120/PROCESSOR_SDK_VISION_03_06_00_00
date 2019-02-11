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
 *  \file     sbl_lib_tda2xx_priv.h
 *
 *  \brief    This file contains the platform specific private layer of
 *            Secondary Bootloader(SBL) Library for TDA2xx SOC Family.
 *            This also contains some related macros.
 */

#ifndef SBL_LIB_TDA2XX_PRIV_H_
#define SBL_LIB_TDA2XX_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  This macro contains the size of OCMC1 (512 KB).
 */
#define SBLLIB_SOC_OCMC_RAM1_SIZE                       ((uint32_t) 0x00080000U)

/**
 * \brief  This macro contains the size of OCMC2 (1 MB).
 */
#define SBLLIB_SOC_OCMC_RAM2_SIZE                       ((uint32_t) 0x00100000U)

/**
 * \brief  This macro contains the size of OCMC3 (1 MB).
 */
#define SBLLIB_SOC_OCMC_RAM3_SIZE                       ((uint32_t) 0x00100000U)

/**
 * \brief  This macro contains the L2 base address of DSP.
 */
#define SBLLIB_SOC_DSP_L2_BASE                          ((uint32_t) 0x00800000U)

/**
 * \brief  This macro contains the L1P base address of DSP.
 */
#define SBLLIB_SOC_DSP_L1P_BASE                         ((uint32_t) 0x00E00000U)

/**
 * \brief  This macro contains the L1D base address of DSP.
 */
#define SBLLIB_SOC_DSP_L1D_BASE                         ((uint32_t) 0x00F00000U)

/**
 * \brief  This macro contains the DMEM base address of EVE.
 */
#define SBLLIB_SOC_EVE_DMEM_BASE                        ((uint32_t) 0x40020000U)

/**
 * \brief  This macro contains the WBUF base address of EVE.
 */
#define SBLLIB_SOC_EVE_WBUF_BASE                        ((uint32_t) 0x40040000U)

/**
 * \brief  This macro contains the IBUF LA base address of EVE.
 */
#define SBLLIB_SOC_EVE_IBUF_LA_BASE                     ((uint32_t) 0x40050000U)

/**
 * \brief  This macro contains the IBUF HA base address of EVE.
 */
#define SBLLIB_SOC_EVE_IBUF_HA_BASE                     ((uint32_t) 0x40054000U)

/**
 * \brief  This macro contains the IBUF LB base address of EVE.
 */
#define SBLLIB_SOC_EVE_IBUF_LB_BASE                     ((uint32_t) 0x40070000U)

/**
 * \brief  This macro contains the IBUF HB base address of EVE.
 */
#define SBLLIB_SOC_EVE_IBUF_HB_BASE                     ((uint32_t) 0x40074000U)

#if defined (__ARM_ARCH_7A__)
/**
 * \brief  This macro contains the base address of EVE1's MMU as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_MMU0_BASE                    (SOC_EVE1_MMU0_BASE)

/**
 * \brief  This macro contains the DMEM base address of EVE1 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_DMEM_BASE                    (SOC_EVE1_DMEM_BASE)

/**
 * \brief  This macro contains the WBUF base address of EVE1 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_WBUF_BASE                    (SOC_EVE1_WBUF_BASE)

/**
 * \brief  This macro contains the IBUF LA base address of EVE1 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_IBUF_LA_BASE                 (SOC_EVE1_IBUFLA_BASE)

/**
 * \brief  This macro contains the IBUF HA base address of EVE1 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_IBUF_HA_BASE                 (SOC_EVE1_IBUFHA_BASE)

/**
 * \brief  This macro contains the IBUF LB base address of EVE1 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_IBUF_LB_BASE                 (SOC_EVE1_IBUFLB_BASE)

/**
 * \brief  This macro contains the IBUF HB base address of EVE1 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_IBUF_HB_BASE                 (SOC_EVE1_IBUFHB_BASE)

/**
 * \brief  This macro contains the TPTC0 base address of EVE1 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_TPTC0_BASE                   (SOC_EVE1_TPTC0_BASE)

/**
 * \brief  This macro contains the TPTC1 base address of EVE1 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE1_TPTC1_BASE                   (SOC_EVE1_TPTC1_BASE)

/**
 * \brief  This macro contains the base address of EVE2's MMU as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_MMU0_BASE                    (SOC_EVE2_MMU0_BASE)

/**
 * \brief  This macro contains the DMEM base address of EVE2 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_DMEM_BASE                    (SOC_EVE2_DMEM_BASE)

/**
 * \brief  This macro contains the WBUF base address of EVE2 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_WBUF_BASE                    (SOC_EVE2_WBUF_BASE)

/**
 * \brief  This macro contains the IBUF LA base address of EVE2 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_IBUF_LA_BASE                 (SOC_EVE2_IBUFLA_BASE)

/**
 * \brief  This macro contains the IBUF HA base address of EVE2 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_IBUF_HA_BASE                 (SOC_EVE2_IBUFHA_BASE)

/**
 * \brief  This macro contains the IBUF LB base address of EVE2 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_IBUF_LB_BASE                 (SOC_EVE2_IBUFLB_BASE)

/**
 * \brief  This macro contains the IBUF HB base address of EVE2 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_IBUF_HB_BASE                 (SOC_EVE2_IBUFHB_BASE)

/**
 * \brief  This macro contains the TPTC0 base address of EVE2 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_TPTC0_BASE                   (SOC_EVE2_TPTC0_BASE)

/**
 * \brief  This macro contains the TPTC1 base address of EVE2 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE2_TPTC1_BASE                   (SOC_EVE2_TPTC1_BASE)

/**
 * \brief  This macro contains the base address of EVE3's MMU as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_MMU0_BASE                    (SOC_EVE3_MMU0_BASE)

/**
 * \brief  This macro contains the DMEM base address of EVE3 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_DMEM_BASE                    (SOC_EVE3_DMEM_BASE)

/**
 * \brief  This macro contains the WBUF base address of EVE3 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_WBUF_BASE                    (SOC_EVE3_WBUF_BASE)

/**
 * \brief  This macro contains the IBUF LA base address of EVE3 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_IBUF_LA_BASE                 (SOC_EVE3_IBUFLA_BASE)

/**
 * \brief  This macro contains the IBUF HA base address of EVE3 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_IBUF_HA_BASE                 (SOC_EVE3_IBUFHA_BASE)

/**
 * \brief  This macro contains the IBUF LB base address of EVE3 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_IBUF_LB_BASE                 (SOC_EVE3_IBUFLB_BASE)

/**
 * \brief  This macro contains the IBUF HB base address of EVE3 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_IBUF_HB_BASE                 (SOC_EVE3_IBUFHB_BASE)

/**
 * \brief  This macro contains the TPTC0 base address of EVE3 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_TPTC0_BASE                   (SOC_EVE3_TPTC0_BASE)

/**
 * \brief  This macro contains the TPTC1 base address of EVE3 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE3_TPTC1_BASE                   (SOC_EVE3_TPTC1_BASE)

/**
 * \brief  This macro contains the base address of EVE4's MMU as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_MMU0_BASE                    (SOC_EVE4_MMU0_BASE)

/**
 * \brief  This macro contains the DMEM base address of EVE4 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_DMEM_BASE                    (SOC_EVE4_DMEM_BASE)

/**
 * \brief  This macro contains the WBUF base address of EVE4 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_WBUF_BASE                    (SOC_EVE4_WBUF_BASE)

/**
 * \brief  This macro contains the IBUF LA base address of EVE4 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_IBUF_LA_BASE                 (SOC_EVE4_IBUFLA_BASE)

/**
 * \brief  This macro contains the IBUF HA base address of EVE4 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_IBUF_HA_BASE                 (SOC_EVE4_IBUFHA_BASE)

/**
 * \brief  This macro contains the IBUF LB base address of EVE4 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_IBUF_LB_BASE                 (SOC_EVE4_IBUFLB_BASE)

/**
 * \brief  This macro contains the IBUF HB base address of EVE4 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_IBUF_HB_BASE                 (SOC_EVE4_IBUFHB_BASE)

/**
 * \brief  This macro contains the TPTC0 base address of EVE4 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_TPTC0_BASE                   (SOC_EVE4_TPTC0_BASE)

/**
 * \brief  This macro contains the TPTC1 base address of EVE4 as accessed from
 *         L3.
 */
#define SBLLIB_SOC_L3_EVE4_TPTC1_BASE                   (SOC_EVE4_TPTC1_BASE)
#endif

/**
 * \brief  This macro contains the EVE core's boot address when there is no
 *         App Image for EVE.
 */
#define SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE                ((uint32_t) 0x80000000U)

/**
 * \brief  This macro contains the EVE core's reset vector address when there
 *         is no App Image for EVE.
 */
#define SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE       ( \
        SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE + 0x100U)

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
 * \brief   Function to execute a ROM/PPA service on a TDA2x/TDA2Ex HS device
 *
 * \param   id    Application ID of ROM/PPA service.
 * \param   flag  Flag to indicate IRQ/FIQ effect on ROM/PPA service
 *                0 => No IRQ/FIQ
 *                1 => Allow IRQ
 *                2 => Allow FIQ
 *                3 => Allow IRQ and FIQ
 * \param   pArgs     Physical address of array of argument list. First entry
 *                    in array must be the number of arguments
 * \param   secTaskId If the ROM/PPA service is interrupted, its ID is saved
 *                    here
 *
 * \retVal  0 On Success, non-zero error-code in case of failure.
 *
 */
int32_t SBLLibHSSecureEntryAsm(uint32_t  id,
                               uint32_t  flag,
                               uint32_t *pArgs,
                               uint32_t *secTaskId);

/**
 * \brief   This function checks the following conditions:
 *            - Check if device type is HS using a control module MMR
 *              for TDA2x/TDA2Ex.
 *            - Check if code is executing on A15. This is needed since
 *              secure functions can only execute on HS devices
 *
 * \retVal  TRUE = Code is running on A15 on a TDA2x/TDA2Ex HS device.
 *          FALSE = All other cases.
 *
 */
uint32_t SblLibIsExecutingOnA15HS(void);

#ifdef __cplusplus
}

#endif

#endif

