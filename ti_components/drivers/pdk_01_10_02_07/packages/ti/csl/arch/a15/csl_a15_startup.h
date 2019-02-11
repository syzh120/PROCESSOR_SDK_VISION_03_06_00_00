/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2017
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
 *  \ingroup CSL_ARCH_A15
 *  \defgroup CSL_ARCH_A15_STARTUP startup
 *
 *  @{
 */
/**
 *  \file   csl_a15_startup.h
 *
 *  \brief  This file contains the API prototypes for interrupt and exception
 *          vectors.
 */
#ifndef A15_STARTUP_H_
#define A15_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_armGicAux.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

void Entry(void);
void UndefInstHandler(void);
void SVC_Handler(void);
void PrefetchAbortHandler(void);
void AbortHandler(void);
void ResvHandler(void);
void IRQHandler(void);
void FIQHandler(void);
Int32 main(void);

#define CSL_ARM_GIC_ENABLE_CACHE        (1U)
#define CSL_ARM_GIC_ENABLE_MMU          (2U)

typedef struct CSL_ArmgicCfg_s {
  uint32_t ctrlBipMap;
} CSL_ArmgicCfg_t;

CSL_ArmGicCpuIntrf*  CSL_armGicGetCpuIfHandler(void);
uint32_t             CSL_armGicIsInitialized(void);
CSL_ArmGicDistIntrf* CSL_armGicGetDistHandler(void);
void CSL_A15_INIT_startup2(const CSL_ArmgicCfg_t *gicCfg);

/* Vector base is defined as weak here - if lnk cmd file defines it,
 * that address would be considred, otherwise the default address
 * would be considered during copy of vector table
 */
extern uint32_t  __vector_base__ __attribute__((weak));

#ifdef __cplusplus
}
#endif
#endif /* A15_STARTUP_H_ */
/** @} */