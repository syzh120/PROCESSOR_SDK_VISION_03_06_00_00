/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 * \file pmlib_cpuidle_utils_a15host.asm
 *
 * \brief This file contains the utils function used for CPU Idle APIs.
 */

/******************************************************************************
 *                                 GLOBAL SYMBOLS
 *****************************************************************************/

        .global PmlibDoWFI
        .global PmlibCpu1Boot

/******************************************************************************
 *                                 CODE SECTION
 *****************************************************************************/

PmlibDoWFI:
    stmfd   sp!, {lr}

    mrc   p15, 0, r0, c1, c0, 1
    bic   r0, r0, #(1 << 6)       @ Disable SMP bit
    mcr   p15, 0, r0, c1, c0, 1

    /*
     * Execute an ISB instruction to ensure that all of the
     * CP15 register changes have been committed.
     */
    isb

    /*
     * Execute a barrier instruction to ensure that all cache,
     * TLB and branch predictor maintenance operations issued
     * by any CPU in the cluster have completed.
     */
    dsb
    dmb

    /*
     * Execute a WFI instruction and wait until the
     * STANDBYWFI output is asserted to indicate that the
     * CPU is in idle and low power state. CPU can specualatively
     * prefetch the instructions so add NOPs after WFI. Sixteen
     * NOPs as per Cortex-A15 pipeline.
     */
    wfi                 @ Wait For Interrupt
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    ldmfd   sp!, {pc}

PmlibCpu1Boot:
    /*
     * Disable SMP bit
     */
    mrc   p15, 0, r0, c1, c0, 1
    bic   r0, r0, #(1 << 6)
    mcr   p15, 0, r0, c1, c0, 1

    /*
     * Execute an ISB instruction to ensure that all of the
     * CP15 register changes have been committed.
     */
    isb
    dsb

    /*
     * Keep CPU1 inside wfi_loop in case waking up from WFI
     * due to wakeup event to avoid executing invalid code
     */
wfi_loop:
    wfi
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    b wfi_loop
