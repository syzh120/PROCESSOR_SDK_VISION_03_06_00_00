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
 *  \file     sbl_utils_tda2xx_iodelay.c
 *
 *  \brief    This file contains the APIs to configure io delay and table
 *            containing delay values valid for TDA2xx SOC family.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda2xx.h>
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

/**
 * \brief   This function calculates the final value to be written to
 *          configuration register using aDelay and gDelay values.
 *
 * \param   aDelay          Value of A delay.
 * \param   gDelay          Value of G Delay.
 * \param   cpde            CPDE Value as previously calculated
 * \param   fpde            FPDE value as previously calculated
 *
 * \return  configRegValue  Calculated Config Register Value
 */
static uint32_t SblUtilsCalculateConfigRegister(uint32_t aDelay,
                                                uint32_t gDelay,
                                                uint32_t cpde,
                                                uint32_t fpde);

/**
 * \brief   This function calculates the delay value for CPDE and FDPE.
 *
 * \param   configRegOffset   Offset Address of Config Register.
 *                            Possible Values:CONFIG_REG_3/CONFIG_REG_4
 * \param   divisorValue      Value of the divisor
 *                            Possible Values: 88  for CONFIG_REG_3
 *                                           264 for CONFIG_REG_4
 *
 * \return  delayVal          Calculated Delay Value
 */
static uint32_t SblUtilsCalculateDelay(uint32_t configRegOffset,
                                       uint32_t divisorValue);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_TDA2XX)
static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadOther_1_0[] = {
#if defined (SOC_DRA75x)
    /* DRA75x pad configuration is shared with PDK board library */
    #include <ti/board/src/evmDRA75x/pinmux/boardPadDelayGpmc_1_0.h>
#else /* SOC_TDA2XX */
    {0x0,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x4,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x8,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0xC,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x10, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x14, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x18, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x1C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x20, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x24, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x28, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x30, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x34, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x38, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x40, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x44, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x48, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x4C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x50, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x54, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x58, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x5C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x60, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x64, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x68, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x6C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x70, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x74, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x78, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x7C, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x80, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x84, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x88, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x8C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x90, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x94, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x98, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x9C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA0, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA4, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA8, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xAC, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xB0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB8, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0xBC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC8, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xCC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8, 0xE000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
#endif
};

static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadNor_1_0[] = {
    {0x0,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x4,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x8,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0xC,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x10, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x14, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x18, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x1C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x20, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x24, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x28, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x2C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x30, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x34, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x38, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x3C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x40, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x44, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x48, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x4C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x50, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x54, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x58, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x5C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x60, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x64, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x68, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x6C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x70, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x74, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x78, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x7C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x80, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x84, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x88, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x8C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x90, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x94, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x98, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x9C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA0, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA4, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA8, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xAC, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xB0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xB8, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xBC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xC8, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xCC, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD0, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8, 0xF0000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
};

static const sblutilsPadDelayConfig_t gPadDelayConfigCommon_1_0[] = {
#if defined (SOC_DRA75x)
    /* DRA75x pad configuration is shared with PDK board library */
    #include <ti/board/src/evmDRA75x/pinmux/boardPadDelayCommon_1_0.h>
#else /* SOC_TDA2XX */
    {0xDC,  0x40100,
      {0x8D0, 0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_CLK0, 0x40100, {CFG_VIN1A_CLK0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xE0,  0xC0106,
      {0xA2C, 0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1B_CLK1, 0xC0006, {N/A}, {N/A}, {N/A}} **/
    {0xE4,  0x40100,
      {0x9FC, 1847,   683}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_DE0, 0x40100, {CFG_VIN1A_DE0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xE8,  0x4010F,
      {0xA08, 2036,   787}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_FLD0, 0x40100, {CFG_VIN1A_FLD0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    ** For FLD Set mux mode to F. If mux mode of FLD is set to 0 CPLD detects
    ** wrong FID value. This can be configured by application if required and
    ** need not be set in SBL.
    **/
    {0xEC,  0x40100,
      {0xA14, 1939,   789}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_HSYNC0, 0x40100, {CFG_VIN1A_HSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0xF0,  0x40100,
      {0xA20, 1807,   893}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_VSYNC0, 0x40100, {CFG_VIN1A_VSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0xF4,  0x40100,
      {0x8DC, 2095,   566}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D0, 0x40100, {CFG_VIN1A_D0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xF8,  0x40100,
      {0x960, 1964,   672}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D1, 0x40100, {CFG_VIN1A_D1_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xFC,  0x40100,
      {0x99C, 1933,   896}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D2, 0x40100, {CFG_VIN1A_D2_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x100, 0x40100,
      {0x9A8, 1963,   786}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D3, 0x40100, {CFG_VIN1A_D3_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x104, 0x40100,
      {0x9B4, 2086,   435}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D4, 0x40100, {CFG_VIN1A_D4_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x108, 0x40100,
      {0x9C0, 1998,   739}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D5, 0x40100, {CFG_VIN1A_D5_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x10C, 0x40100,
      {0x9CC, 1952,   749}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D6, 0x40100, {CFG_VIN1A_D6_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x110, 0x40100,
      {0x9D8, 2061,   726}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D7, 0x40100, {CFG_VIN1A_D7_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x114, 0x4010F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D8, 0x4010F, {N/A}, {N/A}, {N/A}} **/
    {0x118, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x11C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x120, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x124, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x128, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x12C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x130, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x134, 0x40106,
      {0x930, 2272,   1013}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D16, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x138, 0x40106,
      {0x93C, 2359,   972}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D17, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x13C, 0x40106,
      {0x948, 2367,   1051}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D18, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x140, 0x40106,
      {0x954, 2336,   1067}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D19, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x144, 0x40106,
      {0x96C, 2329,   945}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D20, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x148, 0x40106,
      {0x978, 2403,   836}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D21, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x14C, 0x40106,
      {0x984, 2270,   798}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D22, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x150, 0x40106,
      {0x990, 2509,   321}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D23, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x154, 0x40100,
      {0xA38, 0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_CLK0, 0x40100, {CFG_VIN2A_CLK0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x158, 0x40100,
      {0xB64, 1953,   141}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_DE0, 0x40100, {CFG_VIN2A_DE0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x15C, 0x4010F,
      {0xB70, 2200,   258}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_FLD0, 0x40100, {CFG_VIN2A_FLD0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    ** For FLD Set mux mode to F. If mux mode of FLD is set to 0 CPLD detects
    ** wrong FID value. This can be configured by application if required and
    ** need not be set in SBL.
    **/
    {0x160, 0x40100,
      {0xB7C, 2089,   3}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_HSYNC0, 0x40100, {CFG_VIN2A_HSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x164, 0x40100,
      {0xB88, 1822,   0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_VSYNC0, 0x40100, {CFG_VIN2A_VSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x168, 0x40100,
      {0xA44, 1965,   8}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D0, 0x40100, {CFG_VIN2A_D0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x16C, 0x40100,
      {0xAC8, 1993,   329}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D1, 0x40100, {CFG_VIN2A_D1_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x170, 0x40100,
      {0xB04, 1872,   0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D2, 0x40100, {CFG_VIN2A_D2_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x174, 0x40100,
      {0xB10, 2198,   191}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D3, 0x40100, {CFG_VIN2A_D3_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x178, 0x40100,
      {0xB1C, 1886,   0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D4, 0x40100, {CFG_VIN2A_D4_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x17C, 0x40100,
      {0xB28, 2233,   166}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D5, 0x40100, {CFG_VIN2A_D5_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x180, 0x40100,
      {0xB34, 1649,   0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D6, 0x40100, {CFG_VIN2A_D6_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x184, 0x40100,
      {0xB40, 1890,   33}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D7, 0x40100, {CFG_VIN2A_D7_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x188, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x18C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x190, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x194, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x198, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D12, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x19C, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D13, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x1A0, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D14, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x1A4, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D15, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x1A8, 0x40003,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D16, 0x40003, {N/A}, {N/A}, {N/A}} **/
    {0x1AC, 0x40003,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D17, 0x40003, {N/A}, {N/A}, {N/A}} **/
    {0x1B0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D18, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1B4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1B8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1BC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1C0, 0x40105,
      {0xAEC, 1452,   201}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D22, 0x40005, {N/A}, {N/A}, {N/A}} **/
    {0x1C4, 0x40105,
      {0xAF8, 1420,   300}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D23, 0x40005, {N/A}, {N/A}, {N/A}} **/
    {0x1C8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1CC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_DE, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_FLD, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_HSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_VSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1DC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1EC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1FC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x200, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x204, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x208, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x20C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x210, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x214, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x218, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x21C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D16, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x220, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D17, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x224, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D18, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x228, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x22C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x230, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x234, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x238, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x23C, 0xA0000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MDIO_MCLK, 0xA0000, {N/A}, {N/A}, {N/A}} **/
    {0x240, 0xE0000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MDIO_D, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x244, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RMII_MHZ_50_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x248, 0xC010F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART3_RXD, 0xC010F, {N/A}, {N/A}, {N/A}} **/
    {0x24C, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART3_TXD, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x250, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXC, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x254, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXCTL, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x258, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD3, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x25C, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD2, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x260, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD1, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x264, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD0, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x268, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXC, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x26C, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXCTL, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x270, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD3, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x274, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD2, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x278, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD1, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x27C, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD0, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x280, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_USB1_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x284, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_USB2_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x288, 0x60003,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_14, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x28C, 0x60003,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_15, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x290, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_16, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x294, 0x4000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK0, 0x4000E, {N/A}, {N/A}, {N/A}} **/
    {0x298, 0x40107,
      {0xCFC, 0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK1, 0x40107, {CFG_XREF_CLK1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x29C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A8, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_FSX, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2AC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B4, 0xC0107,
      {0x3C0, 3144,   549}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR0, 0xC0107, {CFG_MCASP1_AXR0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2B8, 0xC0107,
      {0x414, 2883,   19}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR1, 0xC0107, {CFG_MCASP1_AXR1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2BC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2CC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D4, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR8, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D8, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR9, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2DC, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR10, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E0, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR11, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E4, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR12, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E8, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR13, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2EC, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR14, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F0, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR15, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F4, 0x40107,
      {0x4A4, 1904,   0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKX, 0x40107, {CFG_MCASP2_ACLKX_IN,
     * VIP3_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x2F8, 0xC0107,
      {0x51C, 2112,   84}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_FSX, 0xC0107, {CFG_MCASP2_FSX_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2FC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x300, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x304, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x308, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x30C, 0xC0107,
      {0x4C8, 2080,   0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR2, 0xC0107, {CFG_MCASP2_AXR2_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x310, 0xC0107,
      {0x4D4, 2580,   118}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR3, 0xC0107, {CFG_MCASP2_AXR3_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x314, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR4, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x318, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR5, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x31C, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR6, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x320, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x324, 0x40107,
      {0x528, 725,    0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_ACLKX, 0x40107, {CFG_MCASP3_ACLKX_IN,
     * VIP3_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x328, 0xC0107,
      {0x54C, 2309,   131}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_FSX, 0xC0107, {CFG_MCASP3_FSX_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x32C, 0xC0107,
      {0x534, 2075,   216}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR0, 0xC0107, {CFG_MCASP3_AXR0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x330, 0xC0107,
      {0x540, 712,    1078}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR1, 0xC0107, {CFG_MCASP3_AXR1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x334, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x338, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x33C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x340, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x344, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x348, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x34C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x350, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x354, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_CLK, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x358, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_CMD, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x35C, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x360, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x364, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT2, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x368, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT3, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x36C, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_SDCD, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x370, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_SDWP, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x374, 0x60109,
      {0xD8,  1615,   2499}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_10, 0x60109, {CFG_GPIO6_10_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x378, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_11, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x37C, 0x60109,
      {0x678, 4232,   1768}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_CLK, 0x60109, {CFG_MMC3_CLK_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x380, 0x60109,
      {0x684, 4131,   1768}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_CMD, 0x60109, {CFG_MMC3_CMD_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x384, 0x60109,
      {0x690, 4012,   1793}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT0, 0x60109, {CFG_MMC3_DAT0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x388, 0x60109,
      {0x69C, 4003,   1681}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT1, 0x60109, {CFG_MMC3_DAT1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x38C, 0x60109,
      {0x6A8, 4117,   1381}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT2, 0x60109, {CFG_MMC3_DAT2_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x390, 0x60109,
      {0x6B4, 4177,   1915}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT3, 0x60109, {CFG_MMC3_DAT3_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x394, 0x60109,
      {0x6C0, 4148,   1574}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT4, 0x60109, {CFG_MMC3_DAT4_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x398, 0x60109,
      {0x6CC, 4137,   1419}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT5, 0x60109, {CFG_MMC3_DAT5_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x39C, 0x60109,
      {0x6D8, 4000,   1614}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT6, 0x60109, {CFG_MMC3_DAT6_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x3A0, 0x60109,
      {0x6E4, 4153,   1287}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT7, 0x60109, {CFG_MMC3_DAT7_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x3A4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3A8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3AC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B0, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B4, 0x6000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B8, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS2, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3E0, 0xC0000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS3, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C4, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_D1, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C8, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_D0, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3CC, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_CS0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D0, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_DCAN1_TX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D4, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_DCAN1_RX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3E0, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_RXD, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x3E4, 0x80000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_TXD, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x3E8, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_CTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3EC, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_RTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3F0, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_RXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F4, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_TXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F8, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_CTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3FC, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_RTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x400, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C1_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x404, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C1_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x408, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C2_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x40C, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C2_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x418, 0x1000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP0, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x41C, 0x1000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP1, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x420, 0x1000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP2, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x424, 0x1000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP3, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x430, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TMS, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x434, 0xE0000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TDI, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x438, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TDO, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x43C, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TCLK, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x440, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TRSTN, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x444, 0x50000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RTCK, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x448, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_EMU0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x44C, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_EMU1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x45C, 0x20000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RESETN, 0x20000, {N/A}, {N/A}, {N/A}} **/
    {0x460, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_NMIN_DSP, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x464, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RSTOUTN, 0x0, {N/A}, {N/A}, {N/A}} **/
#endif
};

static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadOther_2_0[] = {
#if defined (SOC_DRA75x)
    /* DRA75x pad configuration is shared with PDK board library */
    #include <ti/board/src/evmDRA75x/pinmux/boardPadDelayGpmc_2_0.h>
#else /* SOC_TDA2XX */
    {0x0,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x4,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x8,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0xC,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x10, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x14, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x18, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x1C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x20, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x24, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x28, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x30, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x34, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x38, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x40, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x44, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x48, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x4C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x50, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x54, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x58, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x5C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x60, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x64, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x68, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x6C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x70, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x74, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x78, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x7C, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x80, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x84, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x88, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x8C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x90, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x94, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x98, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x9C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA0, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA4, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA8, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xAC, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xB0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB8, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0xBC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC8, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xCC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8, 0xE000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
#endif
};

static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadNor_2_0[] = {
    {0x0,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x4,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x8,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0xC,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x10, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x14, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x18, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x1C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x20, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x24, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x28, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x2C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x30, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x34, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x38, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x3C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x40, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x44, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x48, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x4C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x50, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x54, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x58, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x5C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x60, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x64, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x68, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x6C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x70, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x74, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x78, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x7C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x80, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x84, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x88, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x8C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x90, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x94, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x98, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x9C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA0, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA4, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA8, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xAC, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xB0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xB8, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xBC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xC8, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xCC, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD0, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8, 0xF0000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
};

static const sblutilsPadDelayConfig_t gPadDelayConfigCommon_2_0[] = {
#if defined (SOC_DRA75x)
    /* DRA75x pad configuration is shared with PDK board library */
    #include <ti/board/src/evmDRA75x/pinmux/boardPadDelayCommon_2_0.h>
#else /* SOC_TDA2XX */
    {0xDC,  0x40100,
      {0x8D0, 0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_CLK0, 0x40100, {CFG_VIN1A_CLK0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xE0,  0xC0106,
      {0xA2C, 0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1B_CLK1, 0xC0006, {N/A}, {N/A}, {N/A}} **/
    {0xE4,  0x40100,
      {0x9FC, 1468,   1290}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_DE0, 0x40100, {CFG_VIN1A_DE0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xE8,  0x4010F,
      {0xA08, 1633,   1425}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_FLD0, 0x40100, {CFG_VIN1A_FLD0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    ** For FLD Set mux mode to F. If mux mode of FLD is set to 0 CPLD detects
    ** wrong FID value. This can be configured by application if required and
    ** need not be set in SBL.
    **/
    {0xEC,  0x40100,
      {0xA14, 1561,   1424}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_HSYNC0, 0x40100, {CFG_VIN1A_HSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0xF0,  0x40100,
      {0xA20, 1470,   1369}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_VSYNC0, 0x40100, {CFG_VIN1A_VSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0xF4,  0x40100,
      {0x8DC, 1697,   1087}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D0, 0x40100, {CFG_VIN1A_D0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xF8,  0x40100,
      {0x960, 1589,   1164}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D1, 0x40100, {CFG_VIN1A_D1_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0xFC,  0x40100,
      {0x99C, 1557,   1414}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D2, 0x40100, {CFG_VIN1A_D2_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x100, 0x40100,
      {0x9A8, 1588,   1289}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D3, 0x40100, {CFG_VIN1A_D3_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x104, 0x40100,
      {0x9B4, 1687,   949}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D4, 0x40100, {CFG_VIN1A_D4_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x108, 0x40100,
      {0x9C0, 1616,   1257}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D5, 0x40100, {CFG_VIN1A_D5_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x10C, 0x40100,
      {0x9CC, 1582,   1265}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D6, 0x40100, {CFG_VIN1A_D6_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x110, 0x40100,
      {0x9D8, 1659,   1255}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D7, 0x40100, {CFG_VIN1A_D7_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x114, 0x4010F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D8, 0x4010F, {N/A}, {N/A}, {N/A}} **/
    {0x118, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x11C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x120, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x124, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x128, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x12C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x130, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x134, 0x40106,
      {0x930, 1803,   1679}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D16, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x138, 0x40106,
      {0x93C, 1871,   1654}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D17, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x13C, 0x40106,
      {0x948, 1875,   1742}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D18, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x140, 0x40106,
      {0x954, 1844,   1759}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D19, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x144, 0x40106,
      {0x96C, 1845,   1624}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D20, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x148, 0x40106,
      {0x978, 1906,   1520}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D21, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x14C, 0x40106,
      {0x984, 1807,   1437}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D22, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x150, 0x40106,
      {0x990, 1996,   997}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN1A_D23, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x154, 0x40100,
      {0xA38, 0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_CLK0, 0x40100, {CFG_VIN2A_CLK0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x158, 0x40100,
      {0xB64, 1548,   623}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_DE0, 0x40100, {CFG_VIN2A_DE0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x15C, 0x4010F,
      {0xB70, 1771,   815}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_FLD0, 0x40100, {CFG_VIN2A_FLD0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    ** For FLD Set mux mode to F. If mux mode of FLD is set to 0 CPLD detects
    ** wrong FID value. This can be configured by application if required and
    ** need not be set in SBL.
    **/
    {0x160, 0x40100,
      {0xB7C, 1703,   587}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_HSYNC0, 0x40100, {CFG_VIN2A_HSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x164, 0x40100,
      {0xB88, 1486,   464}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_VSYNC0, 0x40100, {CFG_VIN2A_VSYNC0_IN,
     * VIP1_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x168, 0x40100,
      {0xA44, 1597,   561}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D0, 0x40100, {CFG_VIN2A_D0_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x16C, 0x40100,
      {0xAC8, 1598,   801}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D1, 0x40100, {CFG_VIN2A_D1_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x170, 0x40100,
      {0xB04, 1600,   323}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D2, 0x40100, {CFG_VIN2A_D2_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x174, 0x40100,
      {0xB10, 1765,   720}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D3, 0x40100, {CFG_VIN2A_D3_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x178, 0x40100,
      {0xB1C, 1680,   282}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D4, 0x40100, {CFG_VIN2A_D4_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x17C, 0x40100,
      {0xB28, 1791,   696}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D5, 0x40100, {CFG_VIN2A_D5_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x180, 0x40100,
      {0xB34, 1538,   175}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D6, 0x40100, {CFG_VIN2A_D6_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x184, 0x40100,
      {0xB40, 1546,   451}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D7, 0x40100, {CFG_VIN2A_D7_IN, VIP1_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x188, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x18C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x190, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x194, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    { 0x198, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A70,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D12 -> RGMII1_TXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x19C, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A7C,  219,  101 } },
    /* CTRL_CORE_PAD_VIN2A_D13 -> RGMII1_TXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A0, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A88,   92,   58 } },
    /* CTRL_CORE_PAD_VIN2A_D14 -> RGMII1_TXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A4, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A94,  135,  100 } },
    /* CTRL_CORE_PAD_VIN2A_D15 -> RGMII1_TXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A8, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0AA0,  154,  101 } },
    /* CTRL_CORE_PAD_VIN2A_D16 -> RGMII1_TXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1AC, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0AAC,   78,   27 } },
    /* CTRL_CORE_PAD_VIN2A_D17 -> RGMII1_TXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B0, 0x00040103,
          { 0x0AB0,  411,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D18 -> RGMII1_RXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B4, 0x00040103,
          { 0x0ABC,    0,  382 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D19 -> RGMII1_RXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B8, 0x00040103,
          { 0x0AD4,  320,  750 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D20 -> RGMII1_RXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1BC, 0x00040103,
          { 0x0AE0,  192,  836 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D21 -> RGMII1_RXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    {0x1C0, 0x40105,
      {0xAEC, 1203,   503}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D22, 0x40005, {N/A}, {N/A}, {N/A}} **/
    {0x1C4, 0x40105,
      {0xAF8, 1214,   599}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VIN2A_D23, 0x40005, {N/A}, {N/A}, {N/A}} **/
    {0x1C8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1CC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_DE, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_FLD, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_HSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_VSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1DC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1EC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1FC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x200, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x204, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x208, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x20C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x210, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x214, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x218, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x21C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D16, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x220, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D17, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x224, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D18, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x228, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x22C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x230, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x234, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x238, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_VOUT1_D23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x23C, 0xA0000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MDIO_MCLK, 0xA0000, {N/A}, {N/A}, {N/A}} **/
    {0x240, 0xE0000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MDIO_D, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x244, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RMII_MHZ_50_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x248, 0xC010F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART3_RXD, 0xC010F, {N/A}, {N/A}, {N/A}} **/
    {0x24C, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART3_TXD, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    { 0x250, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0740,   89,    0 } },
    /* CTRL_CORE_PAD_RGMII0_TXC -> RGMII0_TXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x254, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x074C,   15,  125 } },
    /* CTRL_CORE_PAD_RGMII0_TXCTL -> RGMII0_TXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x258, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x077C,  291,  205 } },
    /* CTRL_CORE_PAD_RGMII0_TXD3 -> RGMII0_TXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x25C, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0770,    0,   27 } },
    /* CTRL_CORE_PAD_RGMII0_TXD2 -> RGMII0_TXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x260, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0764,  146,   94 } },
    /* CTRL_CORE_PAD_RGMII0_TXD1 -> RGMII0_TXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x264, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0758,  339,  162 } },
    /* CTRL_CORE_PAD_RGMII0_TXD0 -> RGMII0_TXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x268, 0x00040100,
          { 0x06F0,  260,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXC -> RGMII0_RXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x26C, 0x00040100,
          { 0x06FC,    0, 1412 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXCTL -> RGMII0_RXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x270, 0x00040100,
          { 0x072C,  239, 1216 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD3 -> RGMII0_RXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x274, 0x00040100,
          { 0x0720,  195, 1100 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD2 -> RGMII0_RXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x278, 0x00040100,
          { 0x0714,  139, 1081 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD1 -> RGMII0_RXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x27C, 0x00040100,
          { 0x0708,  123, 1047 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD0 -> RGMII0_RXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */

    {0x280, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_USB1_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x284, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_USB2_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x288, 0x60003,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_14, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x28C, 0x60003,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_15, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x290, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_16, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x294, 0x4000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK0, 0x4000E, {N/A}, {N/A}, {N/A}} **/
    {0x298, 0x40107,
      {0xCFC, 0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK1, 0x40107, {CFG_XREF_CLK1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x29C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_XREF_CLK3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A8, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_FSX, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2AC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B4, 0xC0107,
      {0x3C0, 3144,   549}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR0, 0xC0107, {CFG_MCASP1_AXR0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2B8, 0xC0107,
      {0x414, 2883,   19}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR1, 0xC0107, {CFG_MCASP1_AXR1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2BC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2CC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D4, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR8, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D8, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR9, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2DC, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR10, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E0, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR11, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E4, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR12, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E8, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR13, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2EC, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR14, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F0, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR15, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F4, 0x40107,
      {0x4A4, 1904,   0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKX, 0x40107, {CFG_MCASP2_ACLKX_IN,
     * VIP3_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x2F8, 0xC0107,
      {0x51C, 2112,   84}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_FSX, 0xC0107, {CFG_MCASP2_FSX_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x2FC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x300, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x304, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x308, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x30C, 0xC0107,
      {0x4C8, 2080,   0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR2, 0xC0107, {CFG_MCASP2_AXR2_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x310, 0xC0107,
      {0x4D4, 2580,   118}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR3, 0xC0107, {CFG_MCASP2_AXR3_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x314, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR4, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x318, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR5, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x31C, 0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR6, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x320, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x324, 0x40107,
      {0x528, 725,    0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_ACLKX, 0x40107, {CFG_MCASP3_ACLKX_IN,
     * VIP3_MANUAL1},
     ** {N/A}, {N/A}}
     **/
    {0x328, 0xC0107,
      {0x54C, 2309,   131}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_FSX, 0xC0107, {CFG_MCASP3_FSX_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x32C, 0xC0107,
      {0x534, 2075,   216}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR0, 0xC0107, {CFG_MCASP3_AXR0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x330, 0xC0107,
      {0x540, 712,    1078}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR1, 0xC0107, {CFG_MCASP3_AXR1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x334, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x338, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x33C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x340, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x344, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x348, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x34C, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x350, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x354, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_CLK, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x358, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_CMD, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x35C, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x360, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x364, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT2, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x368, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_DAT3, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x36C, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_SDCD, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x370, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC1_SDWP, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x374, 0x60109,
      {0xD8,  774,    2462}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_10, 0x60109, {CFG_GPIO6_10_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x378, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPIO6_11, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x37C, 0x60109,
      {0x678, 2501,   2822}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_CLK, 0x60109, {CFG_MMC3_CLK_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x380, 0x60109,
      {0x684, 2423,   2826}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_CMD, 0x60109, {CFG_MMC3_CMD_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x384, 0x60109,
      {0x690, 2336,   2820}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT0, 0x60109, {CFG_MMC3_DAT0_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x388, 0x60109,
      {0x69C, 2332,   2710}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT1, 0x60109, {CFG_MMC3_DAT1_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x38C, 0x60109,
      {0x6A8, 1732,   3048}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT2, 0x60109, {CFG_MMC3_DAT2_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x390, 0x60109,
      {0x6B4, 2459,   2969}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT3, 0x60109, {CFG_MMC3_DAT3_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x394, 0x60109,
      {0x6C0, 2436,   2662}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT4, 0x60109, {CFG_MMC3_DAT4_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x398, 0x60109,
      {0x6CC, 2450,   2431}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT5, 0x60109, {CFG_MMC3_DAT5_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x39C, 0x60109,
      {0x6D8, 2332,   2640}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT6, 0x60109, {CFG_MMC3_DAT6_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x3A0, 0x60109,
      {0x6E4, 1799,   2927}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_MMC3_DAT7, 0x60109, {CFG_MMC3_DAT7_IN, VIP3_MANUAL1},
    ** {N/A}, {N/A}}
    **/
    {0x3A4, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3A8, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3AC, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B0, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B4, 0x6000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B8, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS2, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3E0, 0xC0000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI1_CS3, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C0, 0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C4, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_D1, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C8, 0xC000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_D0, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3CC, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_SPI2_CS0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D0, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_DCAN1_TX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D4, 0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_DCAN1_RX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3E0, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_RXD, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x3E4, 0x80000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_TXD, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x3E8, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_CTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3EC, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART1_RTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3F0, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_RXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F4, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_TXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F8, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_CTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3FC, 0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_UART2_RTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x400, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C1_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x404, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C1_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x408, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C2_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x40C, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_I2C2_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x418, 0x1000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP0, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x41C, 0x1000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP1, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x420, 0x1000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP2, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x424, 0x1000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_WAKEUP3, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x430, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TMS, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x434, 0xE0000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TDI, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x438, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TDO, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x43C, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TCLK, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x440, 0x40000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_TRSTN, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x444, 0x50000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RTCK, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x448, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_EMU0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x44C, 0x60000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_EMU1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x45C, 0x20000,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RESETN, 0x20000, {N/A}, {N/A}, {N/A}} **/
    {0x460, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_NMIN_DSP, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x464, 0x0,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_RSTOUTN, 0x0, {N/A}, {N/A}, {N/A}} **/
#endif
};
#elif defined (SOC_TDA2EX)
static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadOther_1_0[] = {
#if defined (SOC_DRA72x)
    /* DRA72x pad configuration is shared with PDK board library */
    #include <ti/board/src/evmDRA72x/pinmux/boardPadDelayGpmc_1_0.h>
#else /* SOC_TDA2EX */
    {0x0,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x4,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x8,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0xC,  0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x10, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x14, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x18, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x1C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x20, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x24, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x28, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x30, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x34, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x38, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C, 0x5000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x40, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x44, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x48, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x4C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x50, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x54, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x58, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x5C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x60, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x64, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x68, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x6C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x70, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x74, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x78, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x7C, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x80, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x84, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x88, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x8C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x90, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x94, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x98, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x9C, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA0, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA4, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA8, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xAC, 0x4000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xB0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB8, 0x70001,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0xBC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC8, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xCC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8, 0xE000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
#endif
};

static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadNor_1_0[] = {
    {0x0,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x4,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x8,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0xC,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x10, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x14, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x18, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x1C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x20, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x24, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x28, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x2C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x30, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x34, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x38, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x3C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x40, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x44, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x48, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x4C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x50, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x54, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x58, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x5C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x60, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x64, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x68, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x6C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x70, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x74, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x78, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x7C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x80, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x84, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x88, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x8C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x90, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x94, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x98, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x9C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA0, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA4, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA8, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xAC, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xB0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xB8, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xBC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xC8, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xCC, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD0, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8, 0xF0000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
};

static const sblutilsPadDelayConfig_t gPadDelayConfigCommon_1_0[] = {
#if defined (SOC_DRA72x)
    /* DRA72x pad configuration is shared with PDK board library */
    #include <ti/board/src/evmDRA72x/pinmux/boardPadDelayCommon_1_0.h>
#else /* SOC_TDA2EX */
    {0xDC,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_CLK0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xE0,   0xC0006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1B_CLK1, 0xC0006, {N/A}, {N/A}, {N/A}} **/
    {0xE4,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_DE0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xE8,   0x4010F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_FLD0, 0x40100, {N/A}, {N/A}, {N/A}}
    ** For FLD Set mux mode to F. If mux mode of FLD is set to 0 CPLD detects
    ** wrong FID value. This can be configured by application if required and
    ** need not be set in SBL.
    **/
    {0xEC,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_HSYNC0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xF0,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_VSYNC0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xF4,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xF8,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D1, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xFC,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D2, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x100,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D3, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x104,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D4, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x108,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D5, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x10C,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D6, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x110,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D7, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x114,  0x4010F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D8, 0x4010F, {N/A}, {N/A}, {N/A}} **/
    {0x118,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x11C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x120,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x124,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x128,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x12C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x130,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x134,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D16, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x138,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D17, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x13C,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D18, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x140,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D19, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x144,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D20, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x148,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D21, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x14C,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D22, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x150,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D23, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x154,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_CLK0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x158,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_DE0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x15C,  0x4010F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_FLD0, 0x40100, {N/A}, {N/A}, {N/A}}
    ** For FLD Set mux mode to F. If mux mode of FLD is set to 0 CPLD detects
    ** wrong FID value. This can be configured by application if required and
    ** need not be set in SBL.
    **/
    {0x160,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_HSYNC0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x164,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_VSYNC0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x168,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x16C,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D1, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x170,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D2, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x174,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D3, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x178,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D4, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x17C,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D5, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x180,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D6, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x184,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D7, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x188,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x18C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x190,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x194,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x198,  0x00010103,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0A70, 1551, 115}},
    /** CTRL_CORE_PAD_VIN2A_D12 -> RGMII1_TXC (PIN_OUTPUT) MANUAL delaymode **/
    {0x19C,  0x00010103,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0A7C, 816,  0}},
    /** CTRL_CORE_PAD_VIN2A_D13 -> RGMII1_TXCTL (PIN_OUTPUT) MANUAL delaymode
    **/
    {0x1A0,  0x00010103,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0A88, 876,  0}},
    /** CTRL_CORE_PAD_VIN2A_D14 -> RGMII1_TXD3 (PIN_OUTPUT) MANUAL delaymode **/
    {0x1A4,  0x00010103,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0A94, 312,  0}},
    /** CTRL_CORE_PAD_VIN2A_D15 -> RGMII1_TXD2 (PIN_OUTPUT) MANUAL delaymode **/
    {0x1A8,  0x00010103,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0AA0, 58,   0}},
    /** CTRL_CORE_PAD_VIN2A_D16 -> RGMII1_TXD1 (PIN_OUTPUT) MANUAL delaymode **/
    {0x1AC,  0x00010103,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0AAC, 0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D17 -> RGMII1_TXD0 (PIN_OUTPUT) MANUAL delaymode **/
    {0x1B0,  0x00050103,
      {0x0AB0, 702,       0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D18 -> RGMII1_RXC (PIN_INPUT) MANUAL delaymode **/
    {0x1B4,  0x00050103,
      {0x0ABC, 136,       976}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D19 -> RGMII1_RXCTL (PIN_INPUT) MANUAL delaymode **/
    {0x1B8,  0x00050103,
      {0x0AD4, 210,       1357}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D20 -> RGMII1_RXD3 (PIN_INPUT) MANUAL delaymode **/
    {0x1BC,  0x00050103,
      {0x0AE0, 189,       1462}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D21 -> RGMII1_RXD2 (PIN_INPUT) MANUAL delaymode **/
    {0x1C0,  0x00050103,
      {0x0AEC, 232,       1278}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D22 -> RGMII1_RXD1 (PIN_INPUT) MANUAL delaymode **/
    {0x1C4,  0x00050103,
      {0x0AF8, 0,         1397}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D23 -> RGMII1_RXD0 (PIN_INPUT) MANUAL delaymode **/
    {0x1C8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1CC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_DE, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_FLD, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_HSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_VSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1DC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1EC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1FC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x200,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x204,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x208,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x20C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x210,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x214,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x218,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x21C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D16, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x220,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D17, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x224,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D18, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x228,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x22C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x230,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x234,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x238,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x23C,  0xA0000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MDIO_MCLK, 0xA0000, {N/A}, {N/A}, {N/A}} **/
    {0x240,  0xE0000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MDIO_D, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x244,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RMII_MHZ_50_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x248,  0xC010F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART3_RXD, 0xC010F, {N/A}, {N/A}, {N/A}} **/
    {0x24C,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART3_TXD, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x250,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_TXC, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x254,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_TXCTL, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x258,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD3, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x25C,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD2, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x260,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD1, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x264,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_TXD0, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x268,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_RXC, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x26C,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_RXCTL, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x270,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD3, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x274,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD2, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x278,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD1, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x27C,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RGMII0_RXD0, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x280,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_USB1_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x284,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_USB2_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x288,  0x60003,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_14, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x28C,  0x60003,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_15, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x290,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_16, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x294,  0x4000E,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_XREF_CLK0, 0x4000E, {N/A}, {N/A}, {N/A}} **/
    {0x298,  0x40107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_XREF_CLK1, 0x40107, {N/A}, {N/A}, {N/A}} **/
    {0x29C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_XREF_CLK2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_XREF_CLK3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A8,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_FSX, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2AC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B4,  0xC0107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR0, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x2B8,  0xC0107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR1, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x2BC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2CC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D4,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR8, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D8,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR9, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2DC,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR10, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E0,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR11, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E4,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR12, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E8,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR13, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2EC,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR14, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F0,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR15, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F4,  0x40107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKX, 0x40107, {N/A}, {N/A}, {N/A}} **/
    {0x2F8,  0xC0107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_FSX, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x2FC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x300,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x304,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x308,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x30C,  0xC0107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR2, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x310,  0xC0107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR3, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x314,  0x1000E,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR4, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x318,  0x1000E,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR5, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x31C,  0x1000E,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR6, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x320,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x324,  0x40107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP3_ACLKX, 0x40107, {N/A}, {N/A}, {N/A}} **/
    {0x328,  0xC0107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP3_FSX, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x32C,  0xC0107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR0, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x330,  0xC0107,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR1, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x334,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP4_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x338,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP4_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x33C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x340,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x344,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP5_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x348,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP5_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x34C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x350,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x354,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_CLK, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x358,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_CMD, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x35C,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_DAT0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x360,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_DAT1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x364,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_DAT2, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x368,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_DAT3, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x36C,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_SDCD, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x370,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_SDWP, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x374,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_10, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x378,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_11, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x37C,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_CLK, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x380,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_CMD, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x384,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT0, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x388,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT1, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x38C,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT2, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x390,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT3, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x394,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT4, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x398,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT5, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x39C,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT6, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x3A0,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT7, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x3A4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3A8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3AC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B0,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B4,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B8,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_CS2, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3BC,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_CS3, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI2_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C4,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI2_D1, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C8,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI2_D0, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3CC,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI2_CS0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D0,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_DCAN1_TX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D4,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_DCAN1_RX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3E0,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART1_RXD, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x3E4,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART1_TXD, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x3E8,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART1_CTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3EC,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART1_RTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3F0,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART2_RXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F4,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART2_TXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F8,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART2_CTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3FC,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART2_RTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x400,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_I2C1_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x404,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_I2C1_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x408,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_I2C2_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x40C,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_I2C2_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x418,  0x1000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_WAKEUP0, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x41C,  0x1000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_WAKEUP1, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x420,  0x1000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_WAKEUP2, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x424,  0x1000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_WAKEUP3, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x430,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TMS, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x434,  0xE0000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TDI, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x438,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TDO, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x43C,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TCLK, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x440,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TRSTN, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x444,  0x50000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RTCK, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x448,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_EMU0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x44C,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_EMU1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x45C,  0x20000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RESETN, 0x20000, {N/A}, {N/A}, {N/A}} **/
    {0x460,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_NMIN_DSP, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x464,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RSTOUTN, 0x0, {N/A}, {N/A}, {N/A}} **/
#endif
};

static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadOther_2_0[] = {
#if defined (SOC_DRA72x)
    /* DRA72x pad configuration is shared with PDK board library */
    #include <ti/board/src/evmDRA72x/pinmux/boardPadDelayGpmc_2_0.h>
#else /* SOC_TDA2EX */
    {0x0,   0x40102,
      {0x264, 2907,   1342}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x4,   0x40102,
      {0x2B8, 2858,   1321}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x8,   0x40102,
      {0x2C4, 2951,   1296}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0xC,   0x40102,
      {0x2D0, 2825,   1154}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x10,  0x40102,
      {0x2DC, 2927,   1245}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x14,  0x40102,
      {0x2E8, 2923,   1251}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x18,  0x40102,
      {0x2F4, 2958,   1342}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x1C,  0x40102,
      {0x300, 2900,   1244}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x20,  0x5000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x24,  0x5000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x28,  0x5000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C,  0x5000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x30,  0x1000E,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x34,  0x5000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x38,  0x5000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C,  0x5000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x5000F, {N/A}, {N/A}, {N/A}} **/
    {0x40,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x44,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x48,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x4C,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x50,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x54,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x58,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x5C,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x60,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x64,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x68,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x6C,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x70,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x74,  0x70001,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x78,  0x70001,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x7C,  0x70001,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x80,  0x70001,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x84,  0x70001,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x88,  0x70001,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0x8C,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x90,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x94,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x98,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x9C,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA0,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA4,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xA8,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xAC,  0x4000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0xB0,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB8,  0x70001,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x70001, {N/A}, {N/A}, {N/A}} **/
    {0xBC,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC8,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xCC,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD0,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD4,  0x6000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8,  0xE000F,
      {0x0,   0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
#endif
};

static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadNor_2_0[] = {
    {0x0,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x4,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x8,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0xC,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x10, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x14, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x18, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x1C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x20, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x24, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x28, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x2C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x30, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x34, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x38, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x3C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x40, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x44, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x48, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x4C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x50, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x54, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x58, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x5C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x60, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x64, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x68, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x6C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x70, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x74, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x78, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x7C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x80, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x84, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x88, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x8C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x90, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x94, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x98, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x9C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA0, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA4, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA8, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xAC, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xB0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xB8, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xBC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xC8, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xCC, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD0, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8, 0xF0000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
};

static const sblutilsPadDelayConfig_t gPadDelayConfigCommon_2_0[] = {
#if defined (SOC_DRA72x)
    /* DRA72x pad configuration is shared with PDK board library */
    #include <ti/board/src/evmDRA72x/pinmux/boardPadDelayCommon_2_0.h>
#else /* SOC_TDA2EX */
    {0xDC,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_CLK0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xE0,   0xC0006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1B_CLK1, 0xC0006, {N/A}, {N/A}, {N/A}} **/
    {0xE4,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_DE0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xE8,   0x4010F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_FLD0, 0x40100, {N/A}, {N/A}, {N/A}}
    ** For FLD Set mux mode to F. If mux mode of FLD is set to 0 CPLD detects
    ** wrong FID value. This can be configured by application if required and
    ** need not be set in SBL.
    **/
    {0xEC,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_HSYNC0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xF0,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_VSYNC0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xF4,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xF8,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D1, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0xFC,   0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D2, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x100,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D3, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x104,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D4, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x108,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D5, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x10C,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D6, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x110,  0x40100,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D7, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x114,  0x4010F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D8, 0x4010F, {N/A}, {N/A}, {N/A}} **/
    {0x118,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x11C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x120,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x124,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x128,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x12C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x130,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x134,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D16, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x138,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D17, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x13C,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D18, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x140,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D19, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x144,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D20, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x148,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D21, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x14C,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D22, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x150,  0x40006,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN1A_D23, 0x40006, {N/A}, {N/A}, {N/A}} **/
    {0x154,  0x40100,
      {0xA38,  0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_CLK0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x158,  0x40100,
      {0xB64,  1732,      208}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_DE0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x15C,  0x4010F,
      {0xB70,  1461,      562}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_FLD0, 0x40100, {N/A}, {N/A}, {N/A}}
    ** For FLD Set mux mode to F. If mux mode of FLD is set to 0 CPLD detects
    ** wrong FID value. This can be configured by application if required and
    ** need not be set in SBL.
    **/
    {0x160,  0x40100,
      {0xB7C,  1877,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_HSYNC0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x164,  0x40100,
      {0xB88,  1566,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_VSYNC0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x168,  0x40100,
      {0xA44,  1812,      102}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D0, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x16C,  0x40100,
      {0xAC8,  1701,      439}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D1, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x170,  0x40100,
      {0xB04,  1675,      35}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D2, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x174,  0x40100,
      {0xB10,  1457,      361}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D3, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x178,  0x40100,
      {0xB1C,  1535,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D4, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x17C,  0x40100,
      {0xB28,  1676,      271}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D5, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x180,  0x40100,
      {0xB34,  1513,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D6, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x184,  0x40100,
      {0xB40,  1616,      141}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D7, 0x40100, {N/A}, {N/A}, {N/A}} **/
    {0x188,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x18C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x190,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x194,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VIN2A_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    { 0x198, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A70,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D12 -> RGMII1_TXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x19C, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A7C,  170,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D13 -> RGMII1_TXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A0, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A88,  150,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D14 -> RGMII1_TXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A4, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A94,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D15 -> RGMII1_TXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A8, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0AA0,   60,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D16 -> RGMII1_TXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1AC, 0x00040103,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0AAC,   60,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D17 -> RGMII1_TXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B0, 0x00040103,
          { 0x0AB0,  530,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D18 -> RGMII1_RXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B4, 0x00040103,
          { 0x0ABC,   71, 1099 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D19 -> RGMII1_RXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B8, 0x00040103,
          { 0x0AD4,  142, 1337 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D20 -> RGMII1_RXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1BC, 0x00040103,
          { 0x0AE0,  114, 1517 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D21 -> RGMII1_RXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    {0x1C0,  0x00050103,
      {0x0AEC, 232,       1278}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D22 -> RGMII1_RXD1 (PIN_INPUT) MANUAL delaymode **/
    {0x1C4,  0x00050103,
      {0x0AF8, 0,         1397}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** CTRL_CORE_PAD_VIN2A_D23 -> RGMII1_RXD0 (PIN_INPUT) MANUAL delaymode **/
    {0x1C8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1CC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_DE, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_FLD, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_HSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1D8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_VSYNC, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1DC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1E8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1EC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1F8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x1FC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D8, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x200,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D9, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x204,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D10, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x208,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D11, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x20C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D12, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x210,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D13, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x214,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D14, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x218,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D15, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x21C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D16, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x220,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D17, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x224,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D18, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x228,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D19, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x22C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D20, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x230,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D21, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x234,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D22, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x238,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_VOUT1_D23, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x23C,  0xC0105,
      {0x5C4,  255,       119}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MDIO_MCLK, 0xA0000, {N/A}, {N/A}, {N/A}} **/
    {0x240,  0xC0105,
      {0x5B8,  1945,      671}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MDIO_D, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x244,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RMII_MHZ_50_CLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x248,  0xC0105,
      {0x8A0,  1829,      747}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART3_RXD, 0xC010F, {N/A}, {N/A}, {N/A}} **/
    {0x24C,  0xC0105,
      {0x8AC,  2030,      837}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART3_TXD, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    { 0x250, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0740,    0,   60 } },
    /* CTRL_CORE_PAD_RGMII0_TXC -> RGMII0_TXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x254, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x074C,    0,   60 } },
    /* CTRL_CORE_PAD_RGMII0_TXCTL -> RGMII0_TXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x258, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x077C,    0,  120 } },
    /* CTRL_CORE_PAD_RGMII0_TXD3 -> RGMII0_TXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x25C, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0770,    0,   60 } },
    /* CTRL_CORE_PAD_RGMII0_TXD2 -> RGMII0_TXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x260, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0764,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_TXD1 -> RGMII0_TXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x264, 0x00040100,
          { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0758,    0,   60 } },
    /* CTRL_CORE_PAD_RGMII0_TXD0 -> RGMII0_TXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x268, 0x00040100,
          { 0x06F0,  413,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXC -> RGMII0_RXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x26C, 0x00040100,
          { 0x06FC,   27, 2296 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXCTL -> RGMII0_RXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x270, 0x00040100,
          { 0x072C,    0, 2057 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD3 -> RGMII0_RXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x274, 0x00040100,
          { 0x0720,   40, 1966 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD2 -> RGMII0_RXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x278, 0x00040100,
          { 0x0714,  134, 1786 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD1 -> RGMII0_RXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x27C, 0x00040100,
          { 0x0708,    3, 1721 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD0 -> RGMII0_RXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    {0x280,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_USB1_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x284,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_USB2_DRVVBUS, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x288,  0x60003,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_14, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x28C,  0x60003,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_15, 0x60003, {N/A}, {N/A}, {N/A}} **/
    {0x290,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_16, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x294,  0x4000E,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_XREF_CLK0, 0x4000E, {N/A}, {N/A}, {N/A}} **/
    {0x298,  0x40107,
      {0xCFC,  0,         192}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_XREF_CLK1, 0x40107, {N/A}, {N/A}, {N/A}} **/
    {0x29C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_XREF_CLK2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_XREF_CLK3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2A8,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_FSX, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2AC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2B4,  0xC010A,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR0, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x2B8,  0xC010A,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR1, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x2BC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR2, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR3, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C4,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR4, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2C8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR5, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2CC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR6, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D4,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR8, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2D8,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR9, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2DC,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR10, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E0,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR11, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E4,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR12, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2E8,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR13, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2EC,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR14, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F0,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP1_AXR15, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x2F4,  0x40107,
      {0x4A4,  2413,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKX, 0x40107, {N/A}, {N/A}, {N/A}} **/
    {0x2F8,  0xC0107,
      {0x51C,  2861,      78}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_FSX, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x2FC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_ACLKR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x300,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_FSR, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x304,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x308,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x30C,  0xC0107,
      {0x4C8,  2478,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR2, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x310,  0xC0107,
      {0x4D4,  2806,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR3, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x314,  0x1000E,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR4, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x318,  0x1000E,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR5, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x31C,  0x1000E,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR6, 0x1000E, {N/A}, {N/A}, {N/A}} **/
    {0x320,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP2_AXR7, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x324,  0x40107,
      {0x528,  1583,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP3_ACLKX, 0x40107, {N/A}, {N/A}, {N/A}} **/
    {0x328,  0xC0107,
      {0x54C,  2792,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP3_FSX, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x32C,  0xC0107,
      {0x534,  2873,      0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR0, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x330,  0xC0107,
      {0x540,  1625,      1400}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP3_AXR1, 0xC0107, {N/A}, {N/A}, {N/A}} **/
    {0x334,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP4_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x338,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP4_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x33C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x340,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP4_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x344,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP5_ACLKX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x348,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP5_FSX, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x34C,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x350,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MCASP5_AXR1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x354,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_CLK, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x358,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_CMD, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x35C,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_DAT0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x360,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_DAT1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x364,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_DAT2, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x368,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_DAT3, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x36C,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_SDCD, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x370,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC1_SDWP, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x374,  0x40104,
      {0xD8,   2829,      884}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_10, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x378,  0x40104,
      {0xE4,   2648,      1033}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_GPIO6_11, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x37C,  0x40104,
      {0x678,  2794,      1074}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_CLK, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x380,  0x40104,
      {0x684,  2789,      1162}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_CMD, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x384,  0x40104,
      {0x690,  2689,      1180}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT0, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x388,  0x40104,
      {0x69C,  2605,      1219}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT1, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x38C,  0x40104,
      {0x6A8,  2616,      703}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT2, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x390,  0x40104,
      {0x6B4,  2760,      1235}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT3, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x394,  0x40104,
      {0x6C0,  2757,      880}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT4, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x398,  0x40104,
      {0x6CC,  2688,      1177}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT5, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x39C,  0x60104,
      {0x6D8,  2638,      1165}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT6, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x3A0,  0x60004,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_MMC3_DAT7, 0x60004, {N/A}, {N/A}, {N/A}} **/
    {0x3A0,  0x40104,
      {0x6E4,  995,       182}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3A8,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_D1, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3AC,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_D0, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B0,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_CS0, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B4,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3B8,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_CS2, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3E0,  0xC0000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI1_CS3, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C0,  0x4000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI2_SCLK, 0x4000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C4,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI2_D1, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3C8,  0xC000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI2_D0, 0xC000F, {N/A}, {N/A}, {N/A}} **/
    {0x3CC,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_SPI2_CS0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D0,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_DCAN1_TX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3D4,  0xE000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_DCAN1_RX, 0xE000F, {N/A}, {N/A}, {N/A}} **/
    {0x3E4,  0x80000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART1_RXD, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x3E4,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART1_TXD, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x3E8,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART1_CTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3EC,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART1_RTSN, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x3F0,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART2_RXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F4,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART2_TXD, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3F8,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART2_CTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x3FC,  0x6000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_UART2_RTSN, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0x400,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_I2C1_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x404,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_I2C1_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x408,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_I2C2_SDA, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x40C,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_I2C2_SCL, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x418,  0x1000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_WAKEUP0, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x41C,  0x1000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_WAKEUP1, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x420,  0x1000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_WAKEUP2, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x424,  0x1000F,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_WAKEUP3, 0x1000F, {N/A}, {N/A}, {N/A}} **/
    {0x430,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TMS, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x434,  0xE0000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TDI, 0xE0000, {N/A}, {N/A}, {N/A}} **/
    {0x438,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TDO, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x43C,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TCLK, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x440,  0x40000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_TRSTN, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x444,  0x50000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RTCK, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x448,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_EMU0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x44C,  0x60000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_EMU1, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0x45C,  0x20000,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RESETN, 0x20000, {N/A}, {N/A}, {N/A}} **/
    {0x460,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_NMIN_DSP, 0x0, {N/A}, {N/A}, {N/A}} **/
    {0x464,  0x0,
      {0x0,    0,         0}, {0x0, 0, 0}, {0x0,    0,    0}},
    /** {CTRL_CORE_PAD_RSTOUTN, 0x0, {N/A}, {N/A}, {N/A}} **/
#endif
};
#endif
#if defined (SOC_TDA2PX)
static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadOther_1_0[] = {
    /* CTRL_CORE_PAD_GPMC_AD0 -> SYSBOOT0 (PIN_INPUT) LEGACY delaymode */
    { 0x000, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD1 -> SYSBOOT1 (PIN_INPUT) LEGACY delaymode */
    { 0x004, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD2 -> SYSBOOT2 (PIN_INPUT) LEGACY delaymode */
    { 0x008, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD3 -> SYSBOOT3 (PIN_INPUT) LEGACY delaymode */
    { 0x00C, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD4 -> SYSBOOT4 (PIN_INPUT) LEGACY delaymode */
    { 0x010, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD5 -> SYSBOOT5 (PIN_INPUT) LEGACY delaymode */
    { 0x014, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD6 -> SYSBOOT6 (PIN_INPUT) LEGACY delaymode */
    { 0x018, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD7 -> SYSBOOT7 (PIN_INPUT) LEGACY delaymode */
    { 0x01C, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD8 -> SYSBOOT8 (PIN_INPUT) LEGACY delaymode */
    { 0x020, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD9 -> SYSBOOT9 (PIN_INPUT) LEGACY delaymode */
    { 0x024, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD10 -> SYSBOOT10 (PIN_INPUT) LEGACY delaymode */
    { 0x028, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD11 -> SYSBOOT11 (PIN_INPUT) LEGACY delaymode */
    { 0x02C, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD12 -> SYSBOOT12 (PIN_INPUT) LEGACY delaymode */
    { 0x030, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD13 -> SYSBOOT13 (PIN_INPUT) LEGACY delaymode */
    { 0x034, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD14 -> SYSBOOT14 (PIN_INPUT) LEGACY delaymode */
    { 0x038, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_AD15 -> SYSBOOT15 (PIN_INPUT) LEGACY delaymode */
    { 0x03C, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A0 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x040, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A1 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x044, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A2 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x048, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A3 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x04C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A4 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x050, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A5 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x054, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A6 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x058, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A7 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x05C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A8 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x060, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A9 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x064, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A10 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x068, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A11 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x06C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A12 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x070, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A13 -> QSPI1_RTCLK (PIN_INPUT) MANUAL delaymode */
    { 0x074, 0x00070101, { 0x0144,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A14 -> QSPI1_D3 (PIN_INPUT) MANUAL delaymode */
    { 0x078, 0x00070101, { 0x0150, 2149, 1052 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A15 -> QSPI1_D2 (PIN_INPUT) MANUAL delaymode */
    { 0x07C, 0x00070101, { 0x015C, 2121,  997 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A16 -> QSPI1_D0 (PIN_INPUT) MANUAL delaymode */
    { 0x080, 0x00070101, { 0x0168, 2159, 1134 }, { 0x0000,    0,    0 }, { 0x0170,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A17 -> QSPI1_D1 (PIN_INPUT) MANUAL delaymode */
    { 0x084, 0x00070101, { 0x0174, 2135, 1085 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A18 -> QSPI1_SCLK (PIN_INPUT) MANUAL delaymode */
    { 0x088, 0x00070101, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0188,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A19 -> DRIVER OFF (PIN_INPUT) LEGACY delaymode */
    { 0x08C, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A20 -> DRIVER OFF (PIN_INPUT) LEGACY delaymode */
    { 0x090, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A21 -> DRIVER OFF (PIN_INPUT) LEGACY delaymode */
    { 0x094, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A22 -> DRIVER OFF (PIN_INPUT) LEGACY delaymode */
    { 0x098, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A23 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x09C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A24 -> DRIVER OFF (PIN_INPUT) LEGACY delaymode */
    { 0x0A0, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A25 -> DRIVER OFF (PIN_INPUT) LEGACY delaymode */
    { 0x0A4, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A26 -> DRIVER OFF (PIN_INPUT) LEGACY delaymode */
    { 0x0A8, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_A27 -> DRIVER OFF (PIN_INPUT) LEGACY delaymode */
    { 0x0AC, 0x0005000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_CS1 -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0B0, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_CS0 -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0B4, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_CS2 -> QSPI1_CS0 (PIN_INPUT) MANUAL delaymode */
    { 0x0B8, 0x00070101, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0374,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_CS3 -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0BC, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_CLK -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0C0, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_ADVN_ALE -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0C4, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_OEN_REN -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0C8, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_WEN -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0CC, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_BEN0 -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0D0, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_BEN1 -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x0D4, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPMC_WAIT0 -> DRIVER OFF (PIN_INPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x0D8, 0x000E000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
};

static const sblutilsPadDelayConfig_t gPadDelayConfigGpmcPadNor_1_0[] = {
    {0x0,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD0, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x4,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD1, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x8,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD2, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0xC,  0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD3, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x10, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD4, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x14, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD5, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x18, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD6, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x1C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD7, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x20, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD8, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x24, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD9, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x28, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD10, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x2C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD11, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x30, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD12, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x34, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD13, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x38, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD14, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x3C, 0x50000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_AD15, 0x50000, {N/A}, {N/A}, {N/A}} **/
    {0x40, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A0, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x44, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A1, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x48, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A2, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x4C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A3, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x50, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A4, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x54, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A5, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x58, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A6, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x5C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A7, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x60, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A8, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x64, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A9, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x68, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A10, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x6C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A11, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x70, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A12, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x74, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A13, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x78, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A14, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x7C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A15, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x80, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A16, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x84, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A17, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x88, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A18, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x8C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A19, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x90, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A20, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x94, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A21, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x98, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A22, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0x9C, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A23, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA0, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A24, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA4, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A25, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xA8, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A26, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xAC, 0x40000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_A27, 0x40000, {N/A}, {N/A}, {N/A}} **/
    {0xB0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xB4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS0, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xB8, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS2, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xBC, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CS3, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC0, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_CLK, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xC4, 0x60000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_ADVN_ALE, 0x60000, {N/A}, {N/A}, {N/A}} **/
    {0xC8, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_OEN_REN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xCC, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WEN, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD0, 0x70000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN0, 0x70000, {N/A}, {N/A}, {N/A}} **/
    {0xD4, 0x6000F,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_BEN1, 0x6000F, {N/A}, {N/A}, {N/A}} **/
    {0xD8, 0xF0000,
      {0x0,  0,      0}, {0x0, 0, 0}, {0x0, 0, 0}},
    /** {CTRL_CORE_PAD_GPMC_WAIT0, 0xE000F, {N/A}, {N/A}, {N/A}} **/
};

static const sblutilsPadDelayConfig_t gPadDelayConfigCommon_1_0[] = {
    /* CTRL_CORE_PAD_VIN1A_CLK0 -> VIN1A_CLK0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x0DC, 0x00040100, { 0x08D0,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1B_CLK1 -> VIN3A_CLK0 (PIN_INPUT_PULLDOWN | SLEWCONTROL) MANUAL delaymode */
    { 0x0E0, 0x000C0106, { 0x0A2C,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_DE0 -> VIN1A_DE0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x0E4, 0x00040100, { 0x09FC, 1842,  861 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_FLD0 -> GPIO3_1 (PIN_OUTPUT) LEGACY delaymode */
    { 0x0E8, 0x0001010E, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_HSYNC0 -> VIN1A_HSYNC0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x0EC, 0x00040100, { 0x0A14, 1871, 1264 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_VSYNC0 -> VIN1A_VSYNC0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x0F0, 0x00040100, { 0x0A20, 1798, 1000 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D0 -> VIN1A_D0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x0F4, 0x00040100, { 0x08DC, 2051,  708 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D1 -> VIN1A_D1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x0F8, 0x00040100, { 0x0960, 1931,  812 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D2 -> VIN1A_D2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x0FC, 0x00040100, { 0x099C, 1871, 1037 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D3 -> VIN1A_D3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x100, 0x00040100, { 0x09A8, 1938,  984 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D4 -> VIN1A_D4 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x104, 0x00040100, { 0x09B4, 2034,  597 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D5 -> VIN1A_D5 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x108, 0x00040100, { 0x09C0, 1961,  927 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D6 -> VIN1A_D6 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x10C, 0x00040100, { 0x09CC, 1909,  930 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D7 -> VIN1A_D7 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x110, 0x00040100, { 0x09D8, 1999,  901 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D8 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x114, 0x0004010F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D9 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x118, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D10 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x11C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D11 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x120, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D12 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x124, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D13 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x128, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D14 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x12C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D15 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x130, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D16 -> VIN3A_D0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x134, 0x00040106, { 0x0930, 2152, 1311 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D17 -> VIN3A_D1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x138, 0x00040106, { 0x093C, 2211, 1381 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D18 -> VIN3A_D2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x13C, 0x00040106, { 0x0948, 2220, 1393 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D19 -> VIN3A_D3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x140, 0x00040106, { 0x0954, 2186, 1418 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D20 -> VIN3A_D4 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x144, 0x00040106, { 0x096C, 2183, 1292 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D21 -> VIN3A_D5 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x148, 0x00040106, { 0x0978, 2280, 1155 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D22 -> VIN3A_D6 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x14C, 0x00040106, { 0x0984, 2144, 1098 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN1A_D23 -> VIN3A_D7 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x150, 0x00040106, { 0x0990, 2355,  643 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_CLK0 -> VIN2A_CLK0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x154, 0x00040100, { 0x0A38,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_DE0 -> VIN2A_DE0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x158, 0x00040100, { 0x0B64, 1772,  316 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_FLD0 -> VIN2A_FLD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x15C, 0x00040100, { 0x0B70, 2117,  507 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_HSYNC0 -> VIN2A_HSYNC0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x160, 0x00040100, { 0x0B7C, 1969,  231 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_VSYNC0 -> VIN2A_VSYNC0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x164, 0x00040100, { 0x0B88, 1793,  110 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D0 -> VIN2A_D0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x168, 0x00040100, { 0x0A44, 1920,  227 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D1 -> VIN2A_D1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x16C, 0x00040100, { 0x0AC8, 1957,  476 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D2 -> VIN2A_D2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x170, 0x00040100, { 0x0B04, 1912,    5 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D3 -> VIN2A_D3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x174, 0x00040100, { 0x0B10, 2095,  421 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D4 -> VIN2A_D4 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x178, 0x00040100, { 0x0B1C, 2008,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D5 -> VIN2A_D5 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x17C, 0x00040100, { 0x0B28, 2137,  406 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D6 -> VIN2A_D6 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x180, 0x00040100, { 0x0B34, 1717,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D7 -> VIN2A_D7 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x184, 0x00040100, { 0x0B40, 1850,  171 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D8 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x188, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D9 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x18C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D10 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x190, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D11 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x194, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D12 -> RGMII1_TXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x198, 0x00040103, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A70,  147,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D13 -> RGMII1_TXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x19C, 0x00040103, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A7C,  110,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D14 -> RGMII1_TXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A0, 0x00040103, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A88,   18,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D15 -> RGMII1_TXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A4, 0x00040103, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0A94,   82,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D16 -> RGMII1_TXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1A8, 0x00040103, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0AA0,   33,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D17 -> RGMII1_TXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1AC, 0x00040103, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0AAC,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D18 -> RGMII1_RXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B0, 0x00040103, { 0x0AB0,  417,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D19 -> RGMII1_RXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B4, 0x00040103, { 0x0ABC,  156,  843 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D20 -> RGMII1_RXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1B8, 0x00040103, { 0x0AD4,  223, 1413 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D21 -> RGMII1_RXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1BC, 0x00040103, { 0x0AE0,  169, 1415 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D22 -> VIN3A_HSYNC0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1C0, 0x00040105, { 0x0AEC, 1667,  213 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VIN2A_D23 -> VIN3A_VSYNC0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1C4, 0x00040105, { 0x0AF8, 1700,  408 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VOUT1_CLK -> VOUT1_CLK (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1C8, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0B9C, 1281,  497 } },
    /* CTRL_CORE_PAD_VOUT1_DE -> VOUT1_DE (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1CC, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0CC8,    0,    0 } },
    /* CTRL_CORE_PAD_VOUT1_FLD -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x1D0, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_VOUT1_HSYNC -> VOUT1_HSYNC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1D4, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0CE0,    0,    0 } },
    /* CTRL_CORE_PAD_VOUT1_VSYNC -> VOUT1_VSYNC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1D8, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0CEC,  815,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D0 -> VOUT1_D0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1DC, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0BA8,  379,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D1 -> VOUT1_D1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1E0, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C2C,  475,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D2 -> VOUT1_D2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1E4, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C68,  264,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D3 -> VOUT1_D3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1E8, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C74,  421,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D4 -> VOUT1_D4 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1EC, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C80, 1257,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D5 -> VOUT1_D5 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1F0, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C8C,  432,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D6 -> VOUT1_D6 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1F4, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C98,  436,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D7 -> VOUT1_D7 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1F8, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0CA4,  440,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D8 -> VOUT1_D8 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x1FC, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0CB0,   81,  100 } },
    /* CTRL_CORE_PAD_VOUT1_D9 -> VOUT1_D9 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x200, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0CBC,  471,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D10 -> VOUT1_D10 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x204, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0BB4,  441,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D11 -> VOUT1_D11 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x208, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0BC0,  461,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D12 -> VOUT1_D12 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x20C, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0BCC, 1189,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D13 -> VOUT1_D13 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x210, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0BD8,  312,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D14 -> VOUT1_D14 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x214, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0BE4,  298,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D15 -> VOUT1_D15 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x218, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0BF0,  284,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D16 -> VOUT1_D16 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x21C, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0BFC,  152,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D17 -> VOUT1_D17 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x220, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C08,  216,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D18 -> VOUT1_D18 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x224, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C14,  408,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D19 -> VOUT1_D19 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x228, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C20,  519,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D20 -> VOUT1_D20 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x22C, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C38,  316,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D21 -> VOUT1_D21 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x230, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C44,   59,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D22 -> VOUT1_D22 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x234, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C50,  221,    0 } },
    /* CTRL_CORE_PAD_VOUT1_D23 -> VOUT1_D23 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x238, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0C5C,   96,    0 } },
    /* CTRL_CORE_PAD_MDIO_MCLK -> MDIO_MCLK (PIN_OUTPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x23C, 0x000A0000, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MDIO_D -> MDIO_D (PIN_INPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x240, 0x000E0000, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RMII_MHZ_50_CLK -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x244, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART3_RXD -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x248, 0x000C010F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART3_TXD -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x24C, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_TXC -> RGMII0_TXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x250, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0740,  121,    0 } },
    /* CTRL_CORE_PAD_RGMII0_TXCTL -> RGMII0_TXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x254, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x074C,   60,    0 } },
    /* CTRL_CORE_PAD_RGMII0_TXD3 -> RGMII0_TXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x258, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x077C,  172,    0 } },
    /* CTRL_CORE_PAD_RGMII0_TXD2 -> RGMII0_TXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x25C, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0770,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_TXD1 -> RGMII0_TXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x260, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0764,   35,    0 } },
    /* CTRL_CORE_PAD_RGMII0_TXD0 -> RGMII0_TXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x264, 0x00040100, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0758,  153,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXC -> RGMII0_RXC (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x268, 0x00040100, { 0x06F0,  451,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXCTL -> RGMII0_RXCTL (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x26C, 0x00040100, { 0x06FC,  127, 1571 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD3 -> RGMII0_RXD3 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x270, 0x00040100, { 0x072C,   28, 1690 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD2 -> RGMII0_RXD2 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x274, 0x00040100, { 0x0720,    0, 1520 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD1 -> RGMII0_RXD1 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x278, 0x00040100, { 0x0714,  136, 1302 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_RGMII0_RXD0 -> RGMII0_RXD0 (PIN_INPUT_PULLDOWN) MANUAL delaymode */
    { 0x27C, 0x00040100, { 0x0708,  165, 1178 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_USB1_DRVVBUS -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x280, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_USB2_DRVVBUS -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x284, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPIO6_14 -> UART10_RXD (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x288, 0x00060003, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPIO6_15 -> UART10_TXD (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x28C, 0x00060003, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPIO6_16 -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x290, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_XREF_CLK0 -> GPIO6_17 (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x294, 0x0004000E, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_XREF_CLK1 -> VIN6A_CLK0 (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x298, 0x00040107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_XREF_CLK2 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x29C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_XREF_CLK3 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2A0, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_ACLKX -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2A4, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_FSX -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2A8, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_ACLKR -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2AC, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_FSR -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2B0, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR0 -> I2C5_SDA (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2B4, 0x000C010A, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR1 -> I2C5_SCL (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2B8, 0x000C010A, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR2 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2BC, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR3 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2C0, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR4 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2C4, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR5 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2C8, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR6 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2CC, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR7 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2D0, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR8 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2D4, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR9 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2D8, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR10 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2DC, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR11 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2E0, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR12 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2E4, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR13 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2E8, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR14 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2EC, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP1_AXR15 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2F0, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_ACLKX -> VIN6A_D7 (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2F4, 0x00040107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_FSX -> VIN6A_D6 (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x2F8, 0x000C0107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_ACLKR -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x2FC, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_FSR -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x300, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_AXR0 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x304, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_AXR1 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x308, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_AXR2 -> VIN6A_D5 (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x30C, 0x000C0107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_AXR3 -> VIN6A_D4 (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x310, 0x000C0107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_AXR4 -> GPIO1_4 (PIN_OUTPUT) LEGACY delaymode */
    { 0x314, 0x0001000E, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_AXR5 -> GPIO6_7 (PIN_OUTPUT) LEGACY delaymode */
    { 0x318, 0x0001000E, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_AXR6 -> GPIO2_29 (PIN_OUTPUT) LEGACY delaymode */
    { 0x31C, 0x0001000E, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP2_AXR7 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x320, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP3_ACLKX -> VIN6A_D3 (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x324, 0x00040107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP3_FSX -> VIN6A_D2 (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x328, 0x000C0107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP3_AXR0 -> VIN6A_D1 (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x32C, 0x000C0107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP3_AXR1 -> VIN6A_D0 (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x330, 0x000C0107, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP4_ACLKX -> I2C4_SDA (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x334, 0x00040004, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP4_FSX -> I2C4_SCL (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x338, 0x00040004, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP4_AXR0 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x33C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP4_AXR1 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x340, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP5_ACLKX -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x344, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP5_FSX -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x348, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP5_AXR0 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x34C, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MCASP5_AXR1 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x350, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC1_SDCD -> DRIVER OFF (PIN_INPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x36C, 0x000E000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC1_SDWP -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x370, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPIO6_10 -> VIN2B_HSYNC1 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x374, 0x00060104, { 0x00D8, 2207,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_GPIO6_11 -> VIN2B_VSYNC1 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x378, 0x00060104, { 0x00E4, 2183,  225 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_CLK -> VIN2B_D7 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x37C, 0x00060104, { 0x0678, 2262,  114 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_CMD -> VIN2B_D6 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x380, 0x00060104, { 0x0684, 2228,  108 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_DAT0 -> VIN2B_D5 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x384, 0x00060104, { 0x0690, 2137,  170 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_DAT1 -> VIN2B_D4 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x388, 0x00060104, { 0x069C, 2116,  154 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_DAT2 -> VIN2B_D3 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x38C, 0x00060104, { 0x06A8, 1891,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_DAT3 -> VIN2B_D2 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x390, 0x00060104, { 0x06B4, 2202,  197 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_DAT4 -> VIN2B_D1 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x394, 0x00060104, { 0x06C0, 1966,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_DAT5 -> VIN2B_D0 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x398, 0x00060104, { 0x06CC, 2163,   15 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_DAT6 -> VIN5A_HSYNC0 (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x39C, 0x00060109, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_MMC3_DAT7 -> VIN2B_CLK1 (PIN_INPUT_PULLUP) MANUAL delaymode */
    { 0x3A0, 0x00060104, { 0x06E4,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI1_SCLK -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x3A4, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI1_D1 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x3A8, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI1_D0 -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x3AC, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI1_CS0 -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x3B0, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI1_CS1 -> GPIO7_11 (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x3B4, 0x0006000E, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI1_CS2 -> DRIVER OFF (PIN_INPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x3B8, 0x000E000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI1_CS3 -> DRIVER OFF (PIN_INPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x3BC, 0x000E000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI2_SCLK -> DRIVER OFF (PIN_INPUT_PULLDOWN) LEGACY delaymode */
    { 0x3C0, 0x0004000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI2_D1 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x3C4, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI2_D0 -> DRIVER OFF (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x3C8, 0x000C000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_SPI2_CS0 -> DRIVER OFF (PIN_INPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x3CC, 0x000E000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_DCAN1_TX -> DRIVER OFF (PIN_INPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x3D0, 0x000E000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_DCAN1_RX -> DRIVER OFF (PIN_INPUT_PULLUP | SLEWCONTROL) LEGACY delaymode */
    { 0x3D4, 0x000E000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART1_RXD -> UART1_RXD (PIN_INPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x3E0, 0x000C0000, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART1_TXD -> UART1_TXD (PIN_OUTPUT_PULLDOWN | SLEWCONTROL) LEGACY delaymode */
    { 0x3E4, 0x00080000, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART1_CTSN -> UART1_CTSN (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x3E8, 0x00060000, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART1_RTSN -> UART1_RTSN (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x3EC, 0x00060000, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART2_RXD -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x3F0, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART2_TXD -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x3F4, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART2_CTSN -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x3F8, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_UART2_RTSN -> DRIVER OFF (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x3FC, 0x0006000F, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_I2C2_SDA -> I2C2_SDA (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x408, 0x00060000, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
    /* CTRL_CORE_PAD_I2C2_SCL -> I2C2_SCL (PIN_INPUT_PULLUP) LEGACY delaymode */
    { 0x40C, 0x00060000, { 0x0000,    0,    0 }, { 0x0000,    0,    0 }, { 0x0000,    0,    0 } },
};
#endif
/* Number of elements should be same in gPadDelayConfigGpmcPadOther_1_0,
 * gPadDelayConfigGpmcPadNor_1_0, gPadDelayConfigGpmcPadOther_2_0 and
 * gPadDelayConfigGpmcPadNor_2_0.
 * Total number of pads is equal to Number of elements in
 * gPadDelayConfigCommon_1_0 and gPadDelayConfigGpmcPadOther_1_0.
 */

static sblutilsPadDelayConfig_t       gPadDelayConfig[
    (sizeof (gPadDelayConfigCommon_1_0) /
     sizeof (sblutilsPadDelayConfig_t)) +
    (sizeof (gPadDelayConfigGpmcPadOther_1_0) /
     sizeof (sblutilsPadDelayConfig_t))];

static sblutilsDelayConfigRegValue_t gPadDelayRegValue[
    (sizeof (gPadDelayConfigCommon_1_0) /
     sizeof (sblutilsPadDelayConfig_t)) +
    (sizeof (gPadDelayConfigGpmcPadOther_1_0) /
     sizeof (sblutilsPadDelayConfig_t))];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

sblutilsPadDelayConfig_t *SBLUtilsGetPadDelayConfigStruct(
    uint32_t *padArraySize, uint32_t bootMode)
{
    sblutilsPadDelayConfig_t *padDelayConfigObj = NULL;
    volatile uint32_t         siliconRev        = SBLLibGetSiliconRev();
    uint32_t arraySize1, arraySize2;
    if (siliconRev < 2U)
    {
        if (bootMode == SBLLIB_BOOT_MODE_NOR)
        {
            arraySize1 = (sizeof (gPadDelayConfigGpmcPadNor_1_0) /
                          sizeof (sblutilsPadDelayConfig_t));
            memcpy(&gPadDelayConfig[0], &gPadDelayConfigGpmcPadNor_1_0[0],
                   sizeof (gPadDelayConfigGpmcPadNor_1_0));
        }
        else
        {
            arraySize1 = (sizeof (gPadDelayConfigGpmcPadOther_1_0) /
                          sizeof (sblutilsPadDelayConfig_t));
            memcpy(&gPadDelayConfig[0], &gPadDelayConfigGpmcPadOther_1_0[0],
                   sizeof (gPadDelayConfigGpmcPadOther_1_0));
        }
        arraySize2 = (sizeof (gPadDelayConfigCommon_1_0) /
                      sizeof (sblutilsPadDelayConfig_t));
        memcpy(&gPadDelayConfig[arraySize1], &gPadDelayConfigCommon_1_0[0],
               sizeof (gPadDelayConfigCommon_1_0));
        *padArraySize     = arraySize1 + arraySize2;
        padDelayConfigObj = gPadDelayConfig;
    }
    else
    {
    #if defined (SOC_TDA2PX)
        /* For TDA2PX, only silicon rev 0 is available */
    #else
        if (bootMode == SBLLIB_BOOT_MODE_NOR)
        {
            arraySize1 = (sizeof (gPadDelayConfigGpmcPadNor_2_0) /
                          sizeof (sblutilsPadDelayConfig_t));
            memcpy(&gPadDelayConfig[0], &gPadDelayConfigGpmcPadNor_2_0[0],
                   sizeof (gPadDelayConfigGpmcPadNor_2_0));
        }
        else
        {
            arraySize1 = (sizeof (gPadDelayConfigGpmcPadOther_2_0) /
                          sizeof (sblutilsPadDelayConfig_t));
            memcpy(&gPadDelayConfig[0], &gPadDelayConfigGpmcPadOther_2_0[0],
                   sizeof (gPadDelayConfigGpmcPadOther_2_0));
        }
        arraySize2 = (sizeof (gPadDelayConfigCommon_2_0) /
                      sizeof (sblutilsPadDelayConfig_t));
        memcpy(&gPadDelayConfig[arraySize1], &gPadDelayConfigCommon_2_0[0],
               sizeof (gPadDelayConfigCommon_2_0));
        *padArraySize     = arraySize1 + arraySize2;
        padDelayConfigObj = gPadDelayConfig;
    #endif
    }
    return (padDelayConfigObj);
}

sblutilsDelayConfigRegValue_t *SBLUtilsGetDelayConfigRegValStruct(
    sblutilsPadDelayConfig_t padDelayConfig[],
    uint32_t                 padArraySize)
{
    uint32_t i;
    uint32_t cpde, fpde, configRegValue, modeSelect;
    cpde = SblUtilsCalculateDelay(CONFIG_REG_3, (uint32_t) 88);
    fpde = SblUtilsCalculateDelay(CONFIG_REG_4, (uint32_t) 264);

    memset(gPadDelayRegValue, (int32_t)0, sizeof(gPadDelayRegValue));
    for (i = 0; i < padArraySize; i++)
    {
        modeSelect = padDelayConfig[i].regVal &
                     CTRL_CORE_PAD_GPMC_AD0_MODE_SELECT_MASK;

        if ((0U != modeSelect) &&
            (0U != padDelayConfig[i].delayConfigIn.offset))
        {
            configRegValue =
                SblUtilsCalculateConfigRegister(
                    padDelayConfig[i].delayConfigIn.aDelay,
                    padDelayConfig[i].delayConfigIn.gDelay,
                    cpde,
                    fpde);

            gPadDelayRegValue[i].configRegValueIn = configRegValue;
        }
        if ((0U != modeSelect) &&
            (0U != padDelayConfig[i].delayConfigOen.offset))
        {
            configRegValue =
                SblUtilsCalculateConfigRegister(
                    padDelayConfig[i].delayConfigOen.aDelay,
                    padDelayConfig[i].delayConfigOen.gDelay,
                    cpde,
                    fpde);

            gPadDelayRegValue[i].configRegValueOen = configRegValue;
        }
        if ((0U != modeSelect) &&
            (0U != padDelayConfig[i].delayConfigOut.offset))
        {
            configRegValue =
                SblUtilsCalculateConfigRegister(
                    padDelayConfig[i].delayConfigOut.aDelay,
                    padDelayConfig[i].delayConfigOut.gDelay,
                    cpde,
                    fpde);

            gPadDelayRegValue[i].configRegValueOut = configRegValue;
        }
    }
    return (gPadDelayRegValue);
}

void SBLUtilsConfigPadMux(sblutilsPadDelayConfig_t      padDelayConfig[],
                          sblutilsDelayConfigRegValue_t padDelayRegValue[],
                          uint32_t                      padArraySize)
{
    uint32_t i, modeSelect;

    for (i = 0; i < padArraySize; i++)
    {
        HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE +
                    (uint32_t) padDelayConfig[i].offset,
                    padDelayConfig[i].regVal);

        modeSelect = padDelayConfig[i].regVal &
                     CTRL_CORE_PAD_GPMC_AD0_MODE_SELECT_MASK;

        if ((0U != modeSelect) &&
            (0U != padDelayConfig[i].delayConfigIn.offset))
        {
            HW_WR_REG32(
                SOC_DELAYLINE_BASE +
                (uint32_t) padDelayConfig[i].delayConfigIn.offset,
                padDelayRegValue[i].configRegValueIn);
        }
        if ((0U != modeSelect) &&
            (0U != padDelayConfig[i].delayConfigOen.offset))
        {
            HW_WR_REG32(
                SOC_DELAYLINE_BASE +
                (uint32_t) padDelayConfig[i].delayConfigOen.offset,
                padDelayRegValue[i].configRegValueOen);
        }
        if ((0U != modeSelect) &&
            (0U != padDelayConfig[i].delayConfigOut.offset))
        {
            HW_WR_REG32(SOC_DELAYLINE_BASE +
                        (uint32_t) padDelayConfig[i].delayConfigOut.offset,
                        padDelayRegValue[i].configRegValueOut);
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */
static uint32_t SblUtilsCalculateConfigRegister(uint32_t aDelay,
                                                uint32_t gDelay,
                                                uint32_t cpde,
                                                uint32_t fpde)
{
    uint32_t gDelayCoarse, gDelayFine, aDelayCoarse, aDelayFine;
    uint32_t coarseElements, fineElements, totalDelay;
    uint32_t finalConfigRegValue = 0U;

    gDelayCoarse = gDelay / 920U;
    gDelayFine   = ((gDelay % 920U) * 10U) / 60U;

    aDelayCoarse = aDelay / cpde;
    aDelayFine   = ((aDelay % cpde) * 10U) / fpde;

    coarseElements = gDelayCoarse + aDelayCoarse;
    fineElements   = (gDelayFine + aDelayFine) / 10U;

    if (22U < fineElements)
    {
        totalDelay     = (coarseElements * cpde) + (fineElements * fpde);
        coarseElements = totalDelay / cpde;
        fineElements   = (totalDelay % cpde) / fpde;
    }

    finalConfigRegValue = (0x29400U ^ (coarseElements << 5U)) + fineElements;

    return finalConfigRegValue;
}

static uint32_t SblUtilsCalculateDelay(uint32_t configRegOffset,
                                       uint32_t divisorValue)
{
    uint32_t refclkPeriod, delayCount, refCount, delayVal;

    refclkPeriod = HW_RD_FIELD32(SOC_DELAYLINE_BASE + CONFIG_REG_2,
                                 CONFIG_REG_2_REFCLK_PERIOD);

    delayCount = HW_RD_FIELD32(SOC_DELAYLINE_BASE + configRegOffset,
                               CONFIG_REG_3_COARSE_DELAY_COUNT);

    refCount = HW_RD_FIELD32(SOC_DELAYLINE_BASE + configRegOffset,
                             CONFIG_REG_3_COARSE_REF_COUNT);

    delayVal = (uint32_t) (((uint64_t) 10 * (uint64_t) (refCount) *
                            (uint64_t) (refclkPeriod)) /
                           ((uint64_t) 2 * (uint64_t) (delayCount) *
                            (uint64_t) (divisorValue)));

    return delayVal;
}

