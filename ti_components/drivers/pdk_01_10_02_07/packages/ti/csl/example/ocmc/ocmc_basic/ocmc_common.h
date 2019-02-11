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

#ifndef OCMC_COMMON_H_
#define OCMC_COMMON_H_

#include <stdint.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif


#define WIDTH  (uint32_t) 8
#define HEIGHT (uint32_t) 6
#define BPP    (uint32_t) 1
#define FRAME_SIZE (WIDTH * HEIGHT * BPS)

#define N_LINES (uint32_t) 2
#define NUM_SLICES_PER_CBUF (uint32_t) 1
#define CBUF_SIZE (WIDTH * BPP * N_LINES * NUM_SLICES_PER_CBUF)

#define cBufSizeInWord  (CBUF_SIZE / 4)

#define OCMC_RAM1_IRQ_CROSS_BAR          (CSL_XBAR_OCMC_RAM1_IRQ)
#define OCMC_RAM1_IRQ_NO                 (25)
#define OCMC_RAM1_IRQ_CROSS_BAR_INSTANCE (3)

uint32_t readSubFrame(uint32_t size, uint32_t *readPointer);
uint32_t writeSubFrame(uint32_t size, uint32_t *writePointer, uint32_t *value);
uint32_t fillBuffer(uint32_t *value, uint32_t startValue, uint32_t size);

void uart_val_print(uint32_t val, char *mess);
void uart_reg_read_print(uint32_t addr, char *mess);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif
