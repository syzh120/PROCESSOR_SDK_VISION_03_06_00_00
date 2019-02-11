/*
 *  Copyright (c) Texas Instruments Incorporated 2012-2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 */


#ifndef SAMPLE_H_
#define SAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif
#define BUFFER_SIZE     (4 * 1024)

/* MAX ACOUNT */
#define MAX_ACOUNT                  (4096)

/* MAX BCOUNT */
#define MAX_BCOUNT                  (1U)
/* MAX CCOUNT */
#define MAX_CCOUNT                  (1U)
/**
 * Buffers (src and dest) are needed for mem-2-mem data transfers.
 * This define is for the MAXIMUM size and hence the maximum data
 * which could be transferred using the sample test cases below.
 */
#define MAX_BUFFER_SIZE             (MAX_ACOUNT * MAX_BCOUNT * MAX_CCOUNT)

#define EDMA3_CC_XFER_COMPLETION_INT_A15                (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (34U)


#if defined (__ARM_ARCH_7A__)
#define EDMA3_CC_XFER_COMPLETION_INT            EDMA3_CC_XFER_COMPLETION_INT_A15
#define EDMA3_CC_XFER_COMPLETION_INT_XBAR_INST  CSL_XBAR_INST_MPU_IRQ_12
#elif defined (__TI_ARM_V7M4__)
#define EDMA3_CC_XFER_COMPLETION_INT            EDMA3_CC_XFER_COMPLETION_INT_M4
#define EDMA3_CC_XFER_COMPLETION_INT_XBAR_INST  CSL_XBAR_INST_IPU1_IRQ_34
#endif

#define EDMA3_CC_REGION_A15                             (0U)
#define EDMA3_CC_REGION_M4                              (1U)

#if defined (__ARM_ARCH_7A__)
#define EDMA3_CC_REGION EDMA3_CC_REGION_A15
#elif defined (__TI_ARM_V7M4__)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M4
#endif

int32_t dma_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                 uint32_t aCnt, uint32_t bCnt,
                 uint32_t cCnt);
int32_t dma_chain_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t ch_num2, uint32_t tcc_num2, uint32_t evtq_num2,
                       uint32_t aCnt,
                       uint32_t bCnt,
                       uint32_t cCnt);
int32_t dma_link_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                      uint32_t edma_paRAM2, uint32_t edma_paRAM3, uint32_t aCnt,
                      uint32_t bCnt,
                      uint32_t cCnt);

int32_t edma_mem_test1(uint32_t ddr_address, uint32_t ch_num, uint32_t tcc_num,
                       uint32_t evtq_num,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt);

int32_t edma_mem_test2(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt,
                       uint32_t bCnt,
                       uint32_t cCnt);

int32_t edma_mem_test3(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt,
                       uint32_t bCnt,
                       uint32_t cCnt);

int32_t edma_mem_test4(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t aCnt,
                       uint32_t bCnt,
                       uint32_t cCnt);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SAMPLE_H_ */
