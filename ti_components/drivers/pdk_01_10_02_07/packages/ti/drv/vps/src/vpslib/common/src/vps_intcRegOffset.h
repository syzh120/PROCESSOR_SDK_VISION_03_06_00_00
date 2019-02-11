/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 */

/**
 *   \file  vps_intcRegOffset.h
 *
 *   This file contains the Register Desciptions for VPS
 *
 */

#ifndef VPS_INTCREGOFFSET_H_
#define VPS_INTCREGOFFSET_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/** \brief Start address of the first DSS interrupt set. */
#define VPS_INTC_SET_START_OFFSET       (0x20U)
/** \brief Size in bytes for each DSS interrupt set. */
#define VPS_INTC_SET_SIZE               (0x20U)

#define VPS_INTC_RAW_SET_REG0           (0x00U)
#define VPS_INTC_RAW_SET_REG1           (0x04U)
#define VPS_INTC_ENABLED_CLR_REG0       (0x08U)
#define VPS_INTC_ENABLED_CLR_REG1       (0x0CU)
#define VPS_INTC_ENABLE_SET_REG0        (0x10U)
#define VPS_INTC_ENABLE_SET_REG1        (0x14U)
#define VPS_INTC_ENABLE_CLR_REG0        (0x18U)
#define VPS_INTC_ENABLE_CLR_REG1        (0x1CU)
#define VPS_INTC_EOI_ADDR               (0xA0U)

#define VIP_FIQ_MASK                    (0x14U)
#define VIP_FIQ_CLEAR                   (0x18U)
#define VIP_FIQ_STATUS                  (0x1CU)

/** \brief Start address of the first VPDMA interrupt set. */
#define VPS_VPDMA_INT_SET_START_OFFSET  (0x40U)
/** \brief Size in bytes for each VPDMA interrupt set. */
#define VPS_VPDMA_INT_SET_SIZE          (0x50U)

/**
 *  \brief This offset should be 0xE0 but using 0xD0 because simulator still
 *  has not interoduced two register which are int_channel6_stat and
 *  int_channel6_mask registers
 */
#define VPDMA_INT_CHANNEL0_INT_STAT     (0x00U)
#define VPDMA_INT_CHANNEL0_INT_MASK     (0x04U)
#define VPDMA_INT_CHANNEL1_INT_STAT     (0x08U)
#define VPDMA_INT_CHANNEL1_INT_MASK     (0x0CU)
#define VPDMA_INT_CHANNEL2_INT_STAT     (0x10U)
#define VPDMA_INT_CHANNEL2_INT_MASK     (0x14U)
#define VPDMA_INT_CHANNEL3_INT_STAT     (0x18U)
#define VPDMA_INT_CHANNEL3_INT_MASK     (0x1CU)
#define VPDMA_INT_CHANNEL4_INT_STAT     (0x20U)
#define VPDMA_INT_CHANNEL4_INT_MASK     (0x24U)
#define VPDMA_INT_CHANNEL5_INT_STAT     (0x28U)
#define VPDMA_INT_CHANNEL5_INT_MASK     (0x2CU)
#define VPDMA_INT_CHANNEL6_INT_STAT     (0x30U)
#define VPDMA_INT_CHANNEL6_INT_MASK     (0x34U)
#define VPDMA_INT_CLIENT0_INT_STAT      (0x38U)
#define VPDMA_INT_CLIENT0_INT_MASK      (0x3CU)
#define VPDMA_INT_CLIENT1_INT_STAT      (0x40U)
#define VPDMA_INT_CLIENT1_INT_MASK      (0x44U)
#define VPDMA_INT_LIST0_INT_STAT        (0x48U)
#define VPDMA_INT_LIST0_INT_MASK        (0x4CU)

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* End of #ifndef VPS_INTCREGOFFSET_H_ */
