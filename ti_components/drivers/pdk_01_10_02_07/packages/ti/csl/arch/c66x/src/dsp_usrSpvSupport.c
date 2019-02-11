/*
 *  Copyright (C) 2016-2017 Texas Instruments Incorporated - http://www.ti.com/
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
#include <c6x.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static void DSP_setupSWENRHandler(void);

#ifdef __cplusplus
extern "C" {
#endif
/* Assembly functions defined in swenr_support.asm */
extern void swenr_rep_setup_asm(void);
extern void switch_cpu_mode_asm(uint32_t mode);
#ifdef __cplusplus
}
#endif

static uint32_t gInitDone = 0U;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
static void DSP_setupSWENRHandler(void)
{
    swenr_rep_setup_asm();
}

uint32_t DSP_getCpuMode(void)
{
    uint32_t mode;
    /* From sprugh7: TSR[6] = CXM, 0 => supervisor, 1=> user mode */
    mode = ((TSR >> 6U) & 0x1U);
    return mode;
}

void DSP_setCpuMode(uint32_t mode)
{
    uint32_t curMode = DSP_getCpuMode();

    if (0U == gInitDone)
    {
        DSP_setupSWENRHandler();
        gInitDone = 1U;
    }

    /* If invalid argument switch to user mode */
    if (mode > 1U)
    {
        mode = 1U;
    }
    if (curMode != mode)
    {
        switch_cpu_mode_asm(mode);
    }
}

/********************************** End Of File ******************************/
