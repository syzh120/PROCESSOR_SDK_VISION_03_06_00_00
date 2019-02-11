/*
 *  Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file     mmu_a15_gcc_asm.h
 *
 *  \brief    This file contains the function declarations for ASM APIs needed
 *            by the A15 MMU HAL.
 */

#ifndef MMU_A15_GCC_ASM_H_
#define MMU_A15_GCC_ASM_H_

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
 * \brief   This function contains the assembly code for initializing the A15
 *          MMU.
 *
 * \param   None.
 *
 * \return  None.
 */
extern void MMUA15InitASM(void);

/**
 * \brief   This function contains assembly instructions for disabling A15 MMU.
 *
 * \param   None.
 *
 * \return  None.
 */
extern void MMUA15DisableASM(void);

/**
 * \brief   This function contains assembly instructions for enabling A15 MMU.
 *
 * \param   firstLevelTableAddr  Address of First Level MMU table
 *
 * \return  None.
 */
extern void MMUA15EnableASM(const uint64_t* firstLevelTableAddr);

/**
 * \brief   This function contains assembly instructions that determine whether
 *          MMU is enabled or not.
 *
 * \param   None.
 *
 * \return  enabledStatus       MMU Enable Status.
 *                              1:Enabled 0:Disabled
 */
extern uint32_t MMUA15IsEnabledASM(void);

/**
 * \brief   This function contains assembly instructions for writing to MAIR
 *          register.
 *
 * \param   attrIndx  Attriute index.
 * \param   attr      Memory attributes.
 *
 * \return  None.
 */
extern void MMUA15WriteMAIRASM(uint32_t attrIndx, uint32_t attr);

/**
 * \brief   This function contain assembly instructions for invalidating the
 *          entire TLB entries for the specified memory range.
 *
 * \param   startAddr    Start Address.
 * \param   len          Length of memory region.
 *
 * \return  None.
 */
extern void MMUA15TLBInvalidateASM(uint32_t startAddr, uint32_t len);

/**
 * \brief   This function contain assembly instructions for invalidating the
 *          entire TLB.
 *
 * \param   None.
 *
 * \return  None.
 */
extern void MMUA15TLBInvalidateAllASM(void);

#ifdef __cplusplus
}

#endif

#endif

