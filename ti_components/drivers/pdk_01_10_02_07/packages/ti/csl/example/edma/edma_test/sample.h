/*
 *  Copyright (C) 2017 Texas Instruments Incorporated
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

#ifndef SAMPLE_H_
#define SAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* MAX ACOUNT */
#define MAX_ACOUNT                  (64U)
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

#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (38U)

#define EDMA3_CC_XFER_COMPLETION_INT_A8                 (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VPSS             (63U)
#define EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO            (62U)
#define EDMA3_CC_XFER_COMPLETION_INT_A15                (12U)
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (34U)

#ifdef BUILD_A8
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A8
#elif defined (_TMS320C6X)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_DSP
#elif defined (BUILD_M3VPSS)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M3VPSS
#elif defined (BUILD_M3VIDEO)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M3VIDEO
#elif defined (__ARM_ARCH_7A__)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_A15
#elif defined (__TI_ARM_V7M4__)
#define EDMA3_CC_XFER_COMPLETION_INT EDMA3_CC_XFER_COMPLETION_INT_M4
#endif

#define EDMA3_CC_REGION_A8                              (0U)
#define EDMA3_CC_REGION_M3VPSS                          (5U)
#define EDMA3_CC_REGION_M3VIDEO                         (4U)
#define EDMA3_CC_REGION_A15                             (0U)
#define EDMA3_CC_REGION_M4                              (1U)

#define EDMA3_CC_REGION_DSP                             (2U)

#ifdef BUILD_A8
#define EDMA3_CC_REGION EDMA3_CC_REGION_A8
#elif defined (_TMS320C6X)
#define EDMA3_CC_REGION EDMA3_CC_REGION_DSP
#elif defined (BUILD_M3VPSS)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M3VPSS
#elif defined (BUILD_M3VIDEO)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M3VIDEO
#elif defined (__ARM_ARCH_7A__)
#define EDMA3_CC_REGION EDMA3_CC_REGION_A15
#elif defined (__TI_ARM_V7M4__)
#define EDMA3_CC_REGION EDMA3_CC_REGION_M4
#endif

int32_t dma_polled(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                   uint32_t aCnt, uint32_t bCnt,
                   uint32_t cCnt);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_TDA3XX)
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

int32_t qdma_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                  uint32_t paramId,
                  uint32_t aCnt, uint32_t bCnt,
                  uint32_t cCnt);

int32_t qdma_link_test(uint32_t ch_num, uint32_t tcc_num, uint32_t evtq_num,
                       uint32_t edma_paRAMId1, uint32_t edma_paRAMId2,
                       uint32_t aCnt, uint32_t bCnt,
                       uint32_t cCnt);
int32_t dma_ping_pong_test(uint32_t chId, uint32_t tcc, uint32_t evtq_num,
                           uint32_t lChId1, uint32_t lChId2);
#endif

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SAMPLE_H_ */

