/*  ============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015-2017
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
/*                         Include Files                                      */
/* ========================================================================== */

#include <ti/csl/tistdtypes.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void CSL_xbarIrqConfigure(CSL_XbarIrqCpuId cpuId,
                          uint32_t irqNumIdx,
                          CSL_XbarIrq xbarIrq)
{
    Int32  retVal = 0;
    uint32_t baseAddr = SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE;
    uint32_t offset, regVal;
    uint32_t regIdx = ((irqNumIdx - 1U) >> 1U);
    uint32_t shift = (((irqNumIdx - 1U) % 2U) * 16U);
    uint32_t mask = (((uint32_t) 0xFFFFU) << shift);

    switch (cpuId)
    {
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
        case CSL_XBAR_IRQ_CPU_ID_MPU:
            if ((0U < irqNumIdx) && (CSL_MPU_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_MPU_IRQ_4_5;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;
#endif

        case CSL_XBAR_IRQ_CPU_ID_IPU1:
            if ((0U < irqNumIdx) && (CSL_IPU1_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_IPU1_IRQ_23_24;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
        case CSL_XBAR_IRQ_CPU_ID_IPU2:
            if ((0U < irqNumIdx) && (CSL_IPU2_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_IPU2_IRQ_23_24;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;
#endif

        case CSL_XBAR_IRQ_CPU_ID_DSP1:
            if ((0U < irqNumIdx) && (CSL_DSP1_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_DSP1_IRQ_32_33;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        case CSL_XBAR_IRQ_CPU_ID_DSP2:
            if ((0U < irqNumIdx) && (CSL_DSP1_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_DSP2_IRQ_32_33;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;

        case CSL_XBAR_IRQ_CPU_ID_EVE1:
            if ((0U < irqNumIdx) && (CSL_EVE1_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_EVE1_IRQ_0_1;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
        case CSL_XBAR_IRQ_CPU_ID_EVE2:
            if ((0U < irqNumIdx) && (CSL_EVE2_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_EVE2_IRQ_0_1;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;

        case CSL_XBAR_IRQ_CPU_ID_EVE3:
            if ((0U < irqNumIdx) && (CSL_EVE3_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_EVE3_IRQ_0_1;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;

        case CSL_XBAR_IRQ_CPU_ID_EVE4:
            if ((0U < irqNumIdx) && (CSL_EVE4_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_EVE4_IRQ_0_1;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) || defined (SOC_TDA2EX) || defined (SOC_DRA72x)
        case CSL_XBAR_IRQ_CPU_ID_PRUSS1:
            if ((0U < irqNumIdx) && (CSL_PRUSS1_IRQ_XBAR_COUNT >= irqNumIdx))
            {
                offset = CTRL_CORE_PRUSS1_IRQ_32_33;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;
#endif
        default:
            retVal = (-(int32_t)1);
            break;
    }

    if ((0 == retVal) && (xbarIrq < CSL_IRQ_XBAR_MAX_COUNT))
    {
        /* MMR2 unlock */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_2,
            CTRL_CORE_MMR_LOCK_2_TOUNLOCK);
#else
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_2,
            CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_TOUNLOCK);
#endif

        offset += (regIdx * 4U);
        regVal = HW_RD_REG32(baseAddr + offset);
        regVal &= ~mask;
        regVal |= (xbarIrq << shift);
        HW_WR_REG32(baseAddr + offset, regVal);

        /* MMR2 lock */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_2,
            CTRL_CORE_MMR_LOCK_2_TOLOCK);
#else
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_2,
            CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_TOLOCK);
#endif
    }

    return;
}

void CSL_xbarDmaConfigure(CSL_XbarDmaCpuId cpuId,
                          uint32_t dmaNumIdx,
                          CSL_XbarDma xbarDma)
{
    Int32  retVal = 0;
    uint32_t baseAddr = SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE;
    uint32_t offset, regVal;
    uint32_t regIdx = ((dmaNumIdx - 1U) >> 1U);
    uint32_t shift = (((dmaNumIdx - 1U) % 2U) * 16U);
    uint32_t mask = (((uint32_t) 0xFFFFU) << shift);

    switch (cpuId)
    {
        case CSL_XBAR_DMA_CPU_ID_EDMA:
            if ((0U < dmaNumIdx) && (CSL_EDMA_XBAR_COUNT >= dmaNumIdx))
            {
                offset = CTRL_CORE_DMA_EDMA_DREQ_0_1;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;
        case CSL_XBAR_DMA_CPU_ID_DSP1_DMA:
            if ((0U < dmaNumIdx) && (CSL_DSP1_DMA_XBAR_COUNT >= dmaNumIdx))
            {
                offset = CTRL_CORE_DMA_EDMA_DREQ_0_1;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;
        case CSL_XBAR_DMA_CPU_ID_DSP2_DMA:
            if ((0U < dmaNumIdx) && (CSL_DSP2_DMA_XBAR_COUNT >= dmaNumIdx))
            {
                offset = CTRL_CORE_DMA_EDMA_DREQ_0_1;
            }
            else
            {
                retVal = (-(int32_t)1);
            }
            break;
        default:
            retVal = (-(int32_t)1);
            break;
    }

    if ((0 == retVal) && (xbarDma < CSL_DMA_XBAR_MAX_COUNT))
    {
        /* MMR2 unlock */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_2,
            CTRL_CORE_MMR_LOCK_2_TOUNLOCK);
#else
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_2,
            CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_TOUNLOCK);
#endif

        offset += (regIdx * 4U);
        regVal = HW_RD_REG32(baseAddr + offset);
        regVal &= ~mask;
        regVal |= (xbarDma << shift);
        HW_WR_REG32(baseAddr + offset, regVal);

        /* MMR2 lock */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_2,
            CTRL_CORE_MMR_LOCK_2_TOLOCK);
#else
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE + CTRL_CORE_MMR_LOCK_2,
            CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_TOLOCK);
#endif
    }

    return;
}

