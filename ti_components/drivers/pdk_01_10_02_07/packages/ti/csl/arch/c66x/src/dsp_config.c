/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DSPSysMmuConfig(uint32_t baseAddr, uint32_t mmuInstance, uint32_t enable,
                     uint32_t mmuAbort)
{
    uint32_t regVal;
    if (0U != mmuAbort)
    {
        if (0U == mmuInstance)
        {
            regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
            regVal |= DSP_MMU_CONFIG_MMU0_ABORT_MASK;
            HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
        }
        else
        {
            regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
            regVal |= DSP_MMU_CONFIG_MMU1_ABORT_MASK;
            HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
        }
    }
    else
    {
        if (0U == mmuInstance)
        {
            regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
            regVal &= ~((uint32_t) DSP_MMU_CONFIG_MMU0_ABORT_MASK);
            HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
        }
        else
        {
            regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
            regVal &= ~((uint32_t) DSP_MMU_CONFIG_MMU1_ABORT_MASK);
            HW_WR_REG32_RAW(baseAddr + DSP_MMU_CONFIG, regVal);
        }
    }

    if (0U != enable)
    {
        regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
        regVal |=
            (((uint32_t) DSP_MMU_CONFIG_MMU0_EN_MASK) <<
             (mmuInstance * DSP_MMU_CONFIG_MMU1_EN_SHIFT));
        HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
    }
    else
    {
        regVal  = HW_RD_REG32(baseAddr + DSP_MMU_CONFIG);
        regVal &=
            (~(((uint32_t) DSP_MMU_CONFIG_MMU0_EN_MASK) <<
               (mmuInstance * DSP_MMU_CONFIG_MMU1_EN_SHIFT)));
        HW_WR_REG32(baseAddr + DSP_MMU_CONFIG, regVal);
    }
}
/********************************** End Of File ******************************/
