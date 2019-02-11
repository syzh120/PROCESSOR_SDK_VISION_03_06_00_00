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

/**
 *  \file   dsp_wugen.c
 *
 *  \brief  DSP Wake up Generator related APIs.
 *
 *   This file contains the APIs for configuring DSP_WUGEN
 *
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MAX_INTERNAL_INTR               (32U)
/** \brief Maximum Number of internal interrupts */

#define REG_IDX_SHIFT                  (0x05U)
/** \brief Register Index */

#define REG_BIT_MASK                   (0x1FU)
/** \brief Register Bit Mask */

#define NUM_BYTES_REG                  (0x4U)
/** \brief Address offset per register */

#define MAX_WAKEUP_EVENTS              (64U)
/** \brief Maximum Number of wakeup events */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/**
 * \brief Configure the wakeup gen register.
 *
 * \param intNum Interrupt number to be set.
 *
 * \return None
 */
void DSP_wugen_setWakeupReg(uint32_t intNum);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void DSP_WUGEN_IRQ_Init(void)
{
    DSP_WUGEN_IRQ_DisableAll();
}

void DSP_WUGEN_IRQ_DisableAll(void)
{
    HW_WR_REG32(SOC_DSP_SYSTEM_BASE + DSP_IRQWAKEEN0, 0);
    HW_WR_REG32(SOC_DSP_SYSTEM_BASE + DSP_IRQWAKEEN1, 0);
}

void DSP_WUGEN_DMAEVENT_Init(void)
{
    DSP_WUGEN_DMAEVENT_DisableAll();
}

void DSP_WUGEN_DMAEVENT_DisableAll(void)
{
    HW_WR_REG32(SOC_DSP_SYSTEM_BASE + DSP_DMAWAKEEN0, 0);
    HW_WR_REG32(SOC_DSP_SYSTEM_BASE + DSP_DMAWAKEEN1, 0);
}

void DSP_WUGEN_IRQ_Interrupt_Lookup(void)
{
    uint32_t index;
    uint32_t regval;
    uint32_t intsel;

    for (index = 0U; index < 3U; index++)
    {
        regval = HW_RD_REG32(SOC_DSP_ICFG_BASE +
                             (DSP_INTMUX1 + (4U * index)));
        intsel = regval & 0xFFU;
        DSP_wugen_setWakeupReg(intsel);
        intsel = (regval & 0xFF00U) >> 8U;
        DSP_wugen_setWakeupReg(intsel);
        intsel = (regval & 0xFF0000U) >> 16U;
        DSP_wugen_setWakeupReg(intsel);
        intsel = (regval & 0xFF000000U) >> 24U;
        DSP_wugen_setWakeupReg(intsel);
    }

    for (index = 0U; index < 2U; index++)
    {
        regval = HW_RD_REG32(SOC_DSP_ICFG_BASE +
                             (DSP_EVTMASK1 + (4U * index)));
        regval = ~(regval);
        regval = HW_RD_REG32(SOC_DSP_SYSTEM_BASE +
                             (DSP_IRQWAKEEN0 + (4U * index))) | regval;
        HW_WR_REG32(SOC_DSP_SYSTEM_BASE +
                    (DSP_IRQWAKEEN0 + (4U * index)),
                    regval);
    }
}

void DSP_WUGEN_IRQ_Enable(uint16_t intrNum)
{
    uint32_t addr, index, mask, shift;
    int32_t  modIntrNum = ((int32_t) intrNum - (int32_t) MAX_INTERNAL_INTR);

    if ((modIntrNum >= 0) && (modIntrNum < ((int32_t) MAX_WAKEUP_EVENTS)))
    {
        index = (uint32_t) modIntrNum >> REG_IDX_SHIFT;
        /* To Handle cases of interrupt numbers being higher than 95 */
        if (index < 2U)
        {
            shift = (uint32_t) modIntrNum & REG_BIT_MASK;
            mask  = ((uint32_t) 1) << shift;
            addr  = SOC_DSP_SYSTEM_BASE +
                    (DSP_IRQWAKEEN0 + (NUM_BYTES_REG * index));

            /* Enable the wakeup event for interrupt number passed */
            HW_WR_FIELD32_RAW(addr,
                              mask,
                              shift,
                              (uint32_t) 1);
        }
    }
}

void DSP_WUGEN_DMAEVENT_Enable(uint16_t dmaEvtNum)
{
    uint32_t addr, index, mask, shift;
    if (dmaEvtNum < CSL_XBAR_INST_DMA_DSP1_DREQ_19)
    {
        index = (uint32_t) dmaEvtNum >> REG_IDX_SHIFT;
        shift = (uint32_t) dmaEvtNum & REG_BIT_MASK;
        mask  = ((uint32_t) 1) << shift;
        addr  = SOC_DSP_SYSTEM_BASE + (DSP_DMAWAKEEN0 + (NUM_BYTES_REG * index));

        /* Enable the wakeup event for dma event number passed */
        HW_WR_FIELD32_RAW(addr,
                          mask,
                          shift,
                          (uint32_t) 1);
    }
}

void DSP_WUGEN_IRQ_Disable(uint16_t intrNum)
{
    uint32_t addr, index, mask, shift;
    int32_t  modIntrNum = ((int32_t) intrNum - (int32_t) MAX_INTERNAL_INTR);

    if ((modIntrNum >= 0) && (modIntrNum < ((int32_t) MAX_WAKEUP_EVENTS)))
    {
        index = (uint32_t) modIntrNum >> REG_IDX_SHIFT;
        shift = (uint32_t) modIntrNum & REG_BIT_MASK;
        mask  = ((uint32_t) 1) << shift;
        addr  = SOC_DSP_SYSTEM_BASE + (DSP_IRQWAKEEN0 + (NUM_BYTES_REG * index));

        /* Enable the wakeup event for interrupt number passed */
        HW_WR_FIELD32_RAW(addr,
                          mask,
                          shift,
                          0);
    }
}

void DSP_WUGEN_DMAEVENT_Disable(uint16_t dmaEvtNum)
{
    uint32_t addr, index, mask, shift;
    if (dmaEvtNum < CSL_XBAR_INST_DMA_DSP1_DREQ_19)
    {
        index = (uint32_t) dmaEvtNum >> REG_IDX_SHIFT;
        shift = (uint32_t) dmaEvtNum & REG_BIT_MASK;
        mask  = ((uint32_t) 1) << shift;
        addr  = SOC_DSP_SYSTEM_BASE + (DSP_DMAWAKEEN0 + (NUM_BYTES_REG * index));

        /* Enable the wakeup event for dma event number passed */
        HW_WR_FIELD32_RAW(addr,
                          mask,
                          shift,
                          0);
    }
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

void DSP_wugen_setWakeupReg(uint32_t intNum)
{
    int32_t  modIntrNum = ((int32_t) intNum - (int32_t) MAX_INTERNAL_INTR);
    uint32_t offset;
    uint32_t shift;
    uint32_t wakeupregval;

    if ((modIntrNum >= 0) && (modIntrNum < ((int32_t) MAX_WAKEUP_EVENTS)))
    {
        offset       = ((uint32_t) modIntrNum / 32U);
        shift        = ((uint32_t) modIntrNum % 32U);
        wakeupregval = HW_RD_REG32(SOC_DSP_SYSTEM_BASE +
                                   (DSP_IRQWAKEEN0 + (4U * offset)));
        wakeupregval = wakeupregval | ((uint32_t) 1 << shift);
        HW_WR_REG32(SOC_DSP_SYSTEM_BASE +
                    (DSP_IRQWAKEEN0 + (4U * offset)),
                    wakeupregval);
    }
}

/********************************** End Of File ******************************/
