/*
 *  Copyright (C) 2013 Texas Instruments Incorporated
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
 *  \file   dma_xbar.c
 *
 *  \brief  DMA XBAR APIs.
 *
 *   This file contains the device abstraction layer APIs for DMA XBAR.
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/platform/dma_xbar.h>
#include <ti/drv/stw_lld/platform/chip_config.h>
#include <ti/csl/soc.h>

/**
 * \brief   This function validates the DMA XBar arguemnts: DMA argument, DMA
 *          Xbar Instance Number, Event Source Number.\n
 *
 * \param   dma                  DMA Id.\n
 *
 * \param   xbarInst             DMA XBar Instance Number. \n
 *
 * \param   eventSource          Event Source Id.  \n
 *
 * \return  dma_xbar_ret_type_t  Possible Return values from DMA XBar. \n
 *
 */
dma_xbar_ret_type_t DMAXBARValidateArgs(dma_id_t dma, uint32_t xbarInst,
                                        xbar_evt_t eventSource)
{
    dma_xbar_ret_type_t retVal = dma_xbar_success;
    /* Validate DMA argument.*/
    if (dma >= 3)
    {
        retVal = invalid_dma_id;
    }

    /* Validate the dma xbar instance number */

    if ((dma_xbar_success == retVal) && (dma == EDMA) &&
        (xbarInst > (uint32_t) EDMA_EVT_XBAR_COUNT))
    {
        retVal = invalid_dma_xbar_inst_id;
    }

    if ((dma_xbar_success == retVal) && (dma == EDMA_DSP1) &&
        (xbarInst > (uint32_t) DSP1_EDMA_EVT_XBAR_COUNT))
    {
        retVal = invalid_dma_xbar_inst_id;
    }
#ifndef SOC_TDA2EX
    if ((dma_xbar_success == retVal) && (dma == EDMA_DSP2) &&
        (xbarInst > (uint32_t) DSP2_EDMA_EVT_XBAR_COUNT))
    {
        retVal = invalid_dma_xbar_inst_id;
    }
#endif

    /* Validate that the event source is legal. */

    if ((dma_xbar_success == retVal) && (eventSource >= DMA_XBAR_MAX_EVT_COUNT))
    {
        retVal = invalid_event_source_id;
    }

    return retVal;
}

/**
 * \brief   This function computes the register address for a valid DMA XBar
 *          instance.\n
 *
 * \param   dma          DMA Id.\n
 *
 * \param   xbarInst     DMA XBar Instance Number. \n
 *
 * \return  register address. \n
 *
 */
uint32_t DMAXBARGetOffset(dma_id_t dma, uint32_t xbarInst)
{
    uint32_t offset;
    uint32_t regOffset;

    if (dma == EDMA)
    {
        offset = CTRL_CORE_DMA_EDMA_DREQ_0_1;
    }

    if (dma == EDMA_DSP1)
    {
        offset = CTRL_CORE_DMA_DSP1_DREQ_0_1;
    }
#ifndef SOC_TDA2EX
    if (dma == EDMA_DSP2)
    {
        offset = CTRL_CORE_DMA_DSP2_DREQ_0_1;
    }
#endif
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
 * \brief   API to set up a connection between an event source and a DMA engine
 *          via the DMA XBAR.\n
 *
 * \param   baseAddr             Memory address of DMA XBAR.\n
 *
 * \param   dma                  DMA ID whose xbar instance is to be setup .\n
 *
 * \param   xbarInst             DMA XBAR instance number to be programmed .\n
 *
 * \param   eventSource          Event source to be selected via the DMA XBAR
 *                               instance .\n
 *
 * \return  dma_xbar_ret_type_t  Possible Return values from DMA XBar. \n
 *
 */
dma_xbar_ret_type_t DMAXBARConnect(uint32_t baseAddr, dma_id_t dma,
                                   uint32_t xbarInst,
                                   xbar_evt_t eventSource)
{
    dma_xbar_ret_type_t ret = dma_xbar_success;
    uint32_t offset;
    uint32_t pos;
    uint32_t val;
    uint32_t tempValue;
    ret = DMAXBARValidateArgs(dma, xbarInst, eventSource);
    if (dma_xbar_success == ret)
    {
        offset = DMAXBARGetOffset(dma, xbarInst);

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
            val = val & 0xffff0000U; /* zero out the lower bitfield */
        }
        else
        {
            /* Even - means, higher bitfield - starting at bit-offset 16 */
            pos = 16U;
            val = val & (uint32_t) 0xffff; /* zero out the higher bitfield */
        }

        val = val | (eventSource << pos);
        HW_WR_REG32(baseAddr + offset, val);
    }
    return ret;
}

/**
 * \brief   API to disconnect any connection between an event source and a dma
 *          engine in the DMA XBAR.\n
 *
 * \param   baseAddr             Memory address of DMA XBAR.\n
 *
 * \param   dma                  DMA ID whose xbar instance is to be
 *                               disconnected.\n
 *
 * \param   xbarInst             DMA XBAR instance number to be disconnected.\n
 *
 * \return  dma_xbar_ret_type_t  Possible Return values from DMA XBar. \n
 *
 */
dma_xbar_ret_type_t DMAXBARDisconnect(uint32_t baseAddr, dma_id_t dma,
                                      uint32_t xbarInst)
{
    dma_xbar_ret_type_t ret = dma_xbar_success;
    uint32_t offset;
    uint32_t pos;
    uint32_t val;
    uint32_t tempValue;

    ret = DMAXBARValidateArgs(dma, xbarInst, DMA_XBAR_RSVD);
    if (dma_xbar_success == ret)
    {
        offset = DMAXBARGetOffset(dma, xbarInst);

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
            val = val & 0xffff0000U; /* zero out the lower bitfield */
        }
        else
        {
            /* Even - means, higher bitfield - starting at bit-offset 16 */
            pos = 16U;
            val = val & (uint32_t) 0xffff; /* zero out the higher bitfield */
        }

        val = val | (DMA_XBAR_RSVD << pos);
        HW_WR_REG32(baseAddr + offset, val);
    }
    return ret;
}

/**
 * \brief   API to read the current connection between a dma engine and an event
 *          source via a dma xbar.\n
 *
 * \param   baseAddr             Memory address of DMA XBAR.\n
 *
 * \param   dma                  DMA ID whose xbar instance configuration is to
 *                               be read.\n
 *
 * \param   xbarInst             DMA XBAR instance number whose configuration is
 *                               to be read.\n
 *
 * \param   eventSource          Event Source that is currently selected via
 *                               this dma xbar.\n
 *
 * \return  dma_xbar_ret_type_t  Possible Return values from DMA XBar. \n
 *
 */
dma_xbar_ret_type_t DMAXBARGetConnection(uint32_t baseAddr, dma_id_t dma,
                                         uint32_t xbarInst,
                                         xbar_evt_t *eventSource)
{
    dma_xbar_ret_type_t ret = dma_xbar_success;
    uint32_t offset;
    uint32_t pos;
    uint32_t val;
    uint32_t tempValue;

    ret = DMAXBARValidateArgs(dma, xbarInst, DMA_XBAR_RSVD);
    if (dma_xbar_success == ret)
    {
        offset = DMAXBARGetOffset(dma, xbarInst);

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

        *eventSource = (xbar_evt_t) ((val >> pos) & (uint32_t) 0xffff);
    }
    return ret;
}

/**
 * \brief   API to check if a DMA XBAR instance is indeed connected to the event
 *          source.\n
 *
 * \param   baseAddr             Memory address of DMA XBAR.\n
 *
 * \param   dma                  DMA ID whose interrupt xbar instance
 *                               configuration is to be verified.\n
 *
 * \param   xbarInst             DMA XBAR instance number whose configuration is
 *                               to be verified.\n
 *
 * \param   eventSource          Event source whose selection is to be
 *                               verified.\n
 *
 * \param   status               Returns 1 if the dma xbar instance has indeed
 *                               selected this source, 0 otherwise.\n
 *
 * \return  dma_xbar_ret_type_t  Possible Return values from DMA XBar. \n
 *
 */
dma_xbar_ret_type_t DMAXBARIsConnected(uint32_t baseAddr, dma_id_t dma,
                                       uint32_t xbarInst,
                                       xbar_evt_t eventSource,
                                       uint8_t *status)
{
    xbar_evt_t          currEventSource;
    dma_xbar_ret_type_t ret = dma_xbar_success;
    ret = DMAXBARGetConnection(baseAddr, dma, xbarInst, &currEventSource);
    if (dma_xbar_success == ret)
    {
        if (currEventSource == eventSource)
        {
            *status = 1U;
        }
        else
        {
            *status = 0U;
        }
    }
    return ret;
}

