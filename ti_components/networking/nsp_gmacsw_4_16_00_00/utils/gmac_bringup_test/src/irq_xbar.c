/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 *  \file   irq_xbar.c
 *
 *  \brief  IRQ XBAR APIs.
 *
 *   This file contains the device abstraction layer APIs for IRQ XBAR.
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include "stdint.h"
#include "hw_types.h"
#include "irq_xbar.h"
#include "chip_config.h"
#include "hw_ctrl_core_irq_dma.h"

/**
 * \brief   This function validates the IRQ XBar arguemnts: CPU argument, IRQ
 *          Xbar Instance Number, Interrupt Source Number.\n
 *
 * \param   cpu                  CPU Id.\n
 *
 * \param   xbarInst             IRQ XBar Instance Number. \n
 *
 * \param   intrSource           Interrupt Source Id.  \n
 *
 * \return  irq_xbar_ret_type_t  Possible Return values from IRQ XBar. \n
 *
 */
irq_xbar_ret_type_t IRQXBARValidateArgs(cpu_id_t cpu, uint32_t xbarInst,
                                        xbar_irq_t intrSource)
{
    irq_xbar_ret_type_t retVal = irq_xbar_success;
    /* Validate CPU argument.*/
    unsigned int numIpus  = CHIPCONFIGGetNumIPUs();
    unsigned int numDsps  = CHIPCONFIGGetNumDSPs();
    unsigned int numEves  = CHIPCONFIGGetNumEVEs();

    if ((irq_xbar_success == retVal) && (cpu == CPU_IPU1) && (numIpus == 0U))
    {
        retVal = invalid_ipu_id;
    }

    if ((irq_xbar_success == retVal) && (cpu == CPU_DSP1) && (numDsps == 0U))
    {
        retVal = invalid_dsp_id;
    }
    if ((irq_xbar_success == retVal) && (cpu == CPU_DSP2) && (numDsps <= 1U))
    {
        retVal = invalid_dsp_id;
    }

    if ((irq_xbar_success == retVal) && (cpu == CPU_EVE1) && (numEves == 0U))
    {
        retVal = invalid_eve_id;
    }

    /* Validate the irq xbar instance number */

    if ((cpu == CPU_IPU1) && (xbarInst > IPU1_IRQ_XBAR_COUNT) &&
        (irq_xbar_success == retVal))
    {
        retVal = invalid_irq_xbar_inst_id;
    }
    if ((cpu == CPU_DSP1) && (xbarInst > DSP1_IRQ_XBAR_COUNT) &&
        (irq_xbar_success == retVal))
    {
        retVal = invalid_irq_xbar_inst_id;
    }
    if ((cpu == CPU_DSP2) && (xbarInst > DSP2_IRQ_XBAR_COUNT) &&
        (irq_xbar_success == retVal))
    {
        retVal = invalid_irq_xbar_inst_id;
    }
    if ((cpu == CPU_EVE1) && (xbarInst > EVE1_IRQ_XBAR_COUNT) &&
        (irq_xbar_success == retVal))
    {
        retVal = invalid_irq_xbar_inst_id;
    }

    /* Validate that the interrupt source is legal. */

    if ((intrSource >= IRQ_XBAR_MAX_COUNT) && (irq_xbar_success == retVal))
    {
        retVal = invalid_intr_source_id;
    }

    return retVal;
}

/**
 * \brief   This function computes the register address for a valid IRQ XBar
 *          instance.\n
 *
 * \param   cpu          CPU Id.\n
 *
 * \param   xbarInst     IRQ XBar Instance Number. \n
 *
 * \return  register address. \n
 *
 */
uint32_t IRQXBARGetOffset(cpu_id_t cpu, uint32_t xbarInst)
{
    uint32_t offset;
    uint32_t regOffset;


    if (cpu == CPU_IPU1)
    {
        offset = CTRL_CORE_IPU1_IRQ_23_24;
    }

    if (cpu == CPU_DSP1)
    {
        offset = CTRL_CORE_DSP1_IRQ_32_33;
    }
    if (cpu == CPU_DSP2)
    {
        offset = CTRL_CORE_DSP2_IRQ_32_33;
    }

    if (cpu == CPU_EVE1)
    {
        offset = CTRL_CORE_EVE1_IRQ_0_1;
    }



    /* Now we add an offset for the xbarInst.
     * This assumes that we are packing two xbar config bitfields per 32-bit
     * reg.
     * i.e. if xbar_inst is n, that means that the bitfield for it is at the
     * register n/2 32-bit offset.*/

    regOffset  = (xbarInst - 1U) >> 1;
    regOffset *= 4U; /* 32-bit MMRs */

    return (offset + regOffset);
}

/**
 * \brief   API to set up a connection between an interrupt source and a
 *          processor via the IRQ XBAR.\n
 *
 * \param   baseAddr             Memory address of IRQ XBAR.\n
 *
 * \param   cpu                  CPU ID whose interrupt xbar instance is to be
 *                               setup .\n
 *
 * \param   xbarInst             IRQ XBAR instance number to be programmed .\n
 *
 * \param   intrSource           Source interrupt to be selected via the IRQ
 *                               XBAR instance .\n
 *
 * \return  irq_xbar_ret_type_t  Possible Return values from IRQ XBar. \n
 *
 */
irq_xbar_ret_type_t IRQXBARConnect(uint32_t baseAddr, cpu_id_t cpu,
                                   uint32_t xbarInst,
                                   xbar_irq_t intrSource)
{
    irq_xbar_ret_type_t ret = irq_xbar_success;
    uint32_t offset;
    uint32_t pos;
    uint32_t val;
    uint32_t tempValue;
    ret = IRQXBARValidateArgs(cpu, xbarInst, intrSource);
    if (irq_xbar_success == ret)
    {
        offset = IRQXBARGetOffset(cpu, xbarInst);

        /* Write to either the high or the low bitfield depending on whether
         * xbarInst is odd or even.
         * This assumes that the MMR contains two bitfields - one per one XBAR
         * instance. */

        val       = HW_RD_REG32(baseAddr + offset);
        tempValue = (uint32_t) (xbarInst & 0x1U);
        if ((uint32_t) 0 != tempValue)
        {
            /* Odd - means, lower bitfield - starting at bit-offset 0 */
            pos = 0U;
            val = val & (uint32_t) 0xffff0000U; /* zero out the lower bitfield
                                                **/
        }
        else
        {
            /* Even - means, higher bitfield - starting at bit-offset 16 */
            pos = 16U;
            val = val & (uint32_t) 0xffff; /* zero out the higher bitfield */
        }

        val = val | (intrSource << pos);
        HW_WR_REG32((baseAddr + offset), val);
    }
    return ret;
}

/**
 * \brief   API to disconnect any connection between an interrupt source and a
 *          processor in the IRQ XBAR.\n
 *
 * \param   baseAddr             Memory address of IRQ XBAR.\n
 *
 * \param   cpu                  CPU ID whose interrupt xbar instance is to be
 *                               disconnected.\n
 *
 * \param   xbarInst             IRQ XBAR instance number to be disconnected.\n
 *
 * \return  irq_xbar_ret_type_t  Possible Return values from IRQ XBar. \n
 *
 */
irq_xbar_ret_type_t IRQXBARDisconnect(uint32_t baseAddr, cpu_id_t cpu,
                                      uint32_t xbarInst)
{
    irq_xbar_ret_type_t ret;
    uint32_t offset;
    uint32_t pos;
    uint32_t val;
    uint32_t tempValue;
    ret = IRQXBARValidateArgs(cpu, xbarInst, IRQ_XBAR_RSVD);
    if (irq_xbar_success == ret)
    {
        offset = IRQXBARGetOffset(cpu, xbarInst);

        /* Write to either the high or the low bitfield depending on whether
         * xbar_inst is odd or even.
         * This assumes that the MMR contains two bitfields - one per one XBAR
         * instance.*/

        val       = HW_RD_REG32(baseAddr + offset);
        tempValue = (uint32_t) (xbarInst & 0x1U);
        if ((uint32_t) 0 != tempValue)
        {
            /* Odd - means, lower bitfield - starting at bit-offset 0 */
            pos = 0U;
            val = val & (uint32_t) 0xffff0000U; /* zero out the lower bitfield
                                                **/
        }
        else
        {
            /* Even - means, higher bitfield - starting at bit-offset 16 */
            pos = 16U;
            val = val & (uint32_t) 0xffff; /* zero out the higher bitfield */
        }

        val = val | (IRQ_XBAR_RSVD << pos);
        HW_WR_REG32((baseAddr + offset), val);
    }
    return ret;
}

/**
 * \brief   API to read the current connection between a CPU and an interrupt
 *          via a irq xbar.\n
 *
 * \param   baseAddr         Memory address of IRQ XBAR.\n
 *
 * \param   cpu              CPU ID whose interrupt xbar instance configuration
 *                           is to be read.\n
 *
 * \param   xbarInst         IRQ XBAR instance number whose configuration is to
 *                           be read.\n
 *
 * \param   intrSource       Source interrupt that is currently selected via
 *                           this irq xbar.\n
 *
 * \return  irq_xbar_ret_type_t  Possible Return values from IRQ XBar. \n
 *
 */
irq_xbar_ret_type_t IRQXBARGetConnection(uint32_t baseAddr, cpu_id_t cpu,
                                         uint32_t xbarInst,
                                         xbar_irq_t *intrSource)
{
    irq_xbar_ret_type_t ret = irq_xbar_success;
    uint32_t offset;
    uint32_t pos;
    uint32_t val;
    uint32_t tempValue;
    ret = IRQXBARValidateArgs(cpu, xbarInst, IRQ_XBAR_RSVD);
    if (ret == irq_xbar_success)
    {
        offset = IRQXBARGetOffset(cpu, xbarInst);

        /* Write to either the high or the low bitfield depending on whether
         * xbar_inst is odd or even.
         * This assumes that the MMR contains two bitfields - one per one XBAR
         * instance.*/

        val       = HW_RD_REG32(baseAddr + offset);
        tempValue = (uint32_t) (xbarInst & 0x1U);
        if ((uint32_t) 0 != tempValue)
        {
            /* Odd - means, lower bitfield - starting at bit-offset 0 */
            pos = 0U;
        }
        else
        {
            /* Even - means, higher bitfield - starting at bit-offset 16 */
            pos = 16U;
        }

        *intrSource = (xbar_irq_t) ((val >> pos) & (uint32_t) 0xffff);
    }
    return ret;
}

/**
 * \brief   API to check if a CPU IRQ XBAR instance is indeed connected to the
 *          interrupt source.\n
 *
 * \param   baseAddr             Memory address of IRQ XBAR.\n
 *
 * \param   cpu                  CPU ID whose interrupt xbar instance
 *                               configuration is to be verified.\n
 *
 * \param   xbarInst             IRQ XBAR instance number whose configuration is
 *                               to be verified.\n
 *
 * \param   intrSource           Interrupt source whose selection is to be
 *                               verified.\n
 *
 * \param   status               Returns 1 if the irq xbar instance has indeed
 *                               selected this source, 0 otherwise.\n
 *
 * \return  irq_xbar_ret_type_t  Possible Return values from IRQ XBar. \n
 *
 */
irq_xbar_ret_type_t IRQXBARIsConnected(uint32_t baseAddr, cpu_id_t cpu,
                                       uint32_t xbarInst,
                                       xbar_irq_t intrSource,
                                       uint8_t *status)
{
    xbar_irq_t          currIntrSource;
    irq_xbar_ret_type_t ret;
    ret = IRQXBARGetConnection(baseAddr, cpu, xbarInst, &currIntrSource);
    if (ret == irq_xbar_success)
    {
        if (currIntrSource == intrSource)
        {
            *status = 1;
        }
        else
        {
            *status = 0;
        }
    }
    return ret;
}

