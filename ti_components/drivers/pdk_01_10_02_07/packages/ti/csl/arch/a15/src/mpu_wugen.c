/*
 * Copyright (c) Texas Instruments Incorporated 2015-2016
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
 *  \file   mpu_wugen.c
 *
 *  \brief  MPU WUGEN related APIs.
 *
 *   This file contains the APIs for configuring MPU_WUGEN
 *   for ARM Cortex-A15 on AM57x and TDA2xx SOC's.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define REG_IDX_SHIFT                  (0x05U)
/** \brief Register Index */

#define REG_BIT_MASK                   (0x1FU)
/** \brief Register Bit Mask */

#define NUM_BYTES_REG                  (uint32_t) (0x4U)
/** \brief Address offset per register */

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

void MPU_WUGEN_Init(void)
{
    MPU_WUGEN_0_DisableAll();
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_AM571x)
 /* Disable not required */
#else
    MPU_WUGEN_1_DisableAll();
#endif
}

void MPU_WUGEN_0_DisableAll(void)
{
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_A_0, 0);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_B_0, 0);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_C_0, 0);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_D_0, 0);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_E_0, 0);
}

void MPU_WUGEN_1_DisableAll(void)
{
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_A_1, 0);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_B_1, 0);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_C_1, 0);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_D_1, 0);
    HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_E_1, 0);
}

void MPU_WUGEN_0_Interrupt_Lookup(void)
{
    uint32_t index;
    uint32_t regval;

    for (index = 0U; index < 5U; index++)
    {
        regval = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ISER1 + (4U * index)));
        HW_WR_REG32(SOC_MPU_WUGEN_BASE +
                    (MPU_WKG_ENB_A_0 + (4U * index)),
                    regval);
    }
}

void MPU_WUGEN_1_Interrupt_Lookup(void)
{
    uint32_t index;
    uint32_t regval;

    for (index = 0U; index < 5U; index++)
    {
        regval = HW_RD_REG32(SOC_INTC_MPU_DISTRIBUTOR_BASE +
                             (MPU_GICD_ISER1 + (4U * index)));
        HW_WR_REG32(SOC_MPU_WUGEN_BASE +
                    (MPU_WKG_ENB_A_1 + (4U * index)),
                    regval);
    }
}

void MPU_WUGEN_0_Enable(uint16_t intrNum)
{
    uint32_t addr, index, mask, shift;

    index = (uint32_t) intrNum >> REG_IDX_SHIFT;
    shift = (uint32_t) intrNum & REG_BIT_MASK;
    mask  = ((uint32_t) 1) << shift;
    addr  = SOC_MPU_WUGEN_BASE + (MPU_WKG_ENB_A_0 + (NUM_BYTES_REG * index));

    /* Enable the wakeup event for interrupt number passed */
    HW_WR_FIELD32_RAW(addr,
                      mask,
                      shift,
                      (uint32_t) 1);
}

void MPU_WUGEN_1_Enable(uint16_t intrNum)
{
    uint32_t addr, index, mask, shift;

    index = (uint32_t) intrNum >> REG_IDX_SHIFT;
    shift = (uint32_t) intrNum & REG_BIT_MASK;
    mask  = ((uint32_t) 1) << shift;
    addr  = SOC_MPU_WUGEN_BASE + (MPU_WKG_ENB_A_1 + (NUM_BYTES_REG * index));

    /* Enable the wakeup event for interrupt number passed */
    HW_WR_FIELD32_RAW(addr,
                      mask,
                      shift,
                      (uint32_t) 1);
}

void MPU_WUGEN_0_Disable(uint16_t intrNum)
{
    uint32_t addr, index, mask, shift;

    index = (uint32_t) intrNum >> REG_IDX_SHIFT;
    shift = (uint32_t) intrNum & REG_BIT_MASK;
    mask  = ((uint32_t) 1) << shift;
    addr  = SOC_MPU_WUGEN_BASE + (MPU_WKG_ENB_A_0 + (NUM_BYTES_REG * index));

    /* Enable the wakeup event for interrupt number passed */
    HW_WR_FIELD32_RAW(addr,
                      mask,
                      shift,
                      0);
}

void MPU_WUGEN_1_Disable(uint16_t intrNum)
{
    uint32_t addr, index, mask, shift;

    index = (uint32_t) intrNum >> REG_IDX_SHIFT;
    shift = (uint32_t) intrNum & REG_BIT_MASK;
    mask  = ((uint32_t) 1) << shift;
    addr  = SOC_MPU_WUGEN_BASE + (MPU_WKG_ENB_A_1 + (NUM_BYTES_REG * index));

    /* Enable the wakeup event for interrupt number passed */
    HW_WR_FIELD32_RAW(addr,
                      mask,
                      shift,
                      0);
}
