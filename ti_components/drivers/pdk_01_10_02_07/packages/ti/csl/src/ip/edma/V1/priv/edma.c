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
 *  \file   edma.c
 *
 *  \brief This file contains device abstraction layer APIs for the EDMA device.
 *         There are APIs here to enable the EDMA instance, set the required
 *         configurations for communication, transmit or receive data.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/hw_types.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**
 *  \brief   The regionId is the shadow region
 *
 **/
static uint32_t gEdmaRegionId = 0;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void EDMA3Init(uint32_t baseAddr, uint32_t queNum)
{
    uint32_t count = 0;
    uint32_t i     = 0;
    uint32_t qnumValue, ccCfg;

    /* Clear the Event miss Registers                                       */
    HW_WR_REG32(baseAddr + EDMA_TPCC_EMCR, EDMA3_SET_ALL_BITS);
    HW_WR_REG32(baseAddr + EDMA_TPCC_EMCRH, EDMA3_SET_ALL_BITS);

    HW_WR_REG32(baseAddr + EDMA_TPCC_QEMCR, EDMA3_SET_ALL_BITS);

    /* Clear CCERR register                                                 */
    HW_WR_REG32(baseAddr + EDMA_TPCC_CCERRCLR, EDMA3_SET_ALL_BITS);

    /* Disable and clear DMA events for all dma channels */
    for (i = 0; i < SOC_EDMA3_NUM_DMACH; i++)
    {
        EDMA3DisableDmaEvt(baseAddr, i);
        EDMA3ClrEvt(baseAddr, i);
        EDMA3ClrMissEvt(baseAddr, i);
    }
    /* Disable and clear channel interrupts for all dma channels */
    for (i = 0; i < EDMA3_NUM_TCC; i++)
    {
        EDMA3DisableEvtIntr(baseAddr, i);
        EDMA3ClrIntr(baseAddr, i);
    }
    /* Disable and clear channel interrupts for all qdma channels */
    for (i = 0; i < SOC_EDMA3_NUM_QDMACH; i++)
    {
         EDMA3DisableQdmaEvt(baseAddr, i);
         EDMA3QdmaClrMissEvt(baseAddr, i);
    }

    /* FOR TYPE EDMA*/
    /* Enable the DMA (0 - 64) channels in the DRAE and DRAEH register */

    HW_WR_REG32(baseAddr + EDMA_TPCC_DRAEM(gEdmaRegionId), EDMA3_SET_ALL_BITS);
    HW_WR_REG32(baseAddr + EDMA_TPCC_DRAEHM(gEdmaRegionId), EDMA3_SET_ALL_BITS);

    /* Bug Fix - Removed the EDMAVersionGet */
    ccCfg = HW_RD_REG32(baseAddr + EDMA_TPCC_CCCFG);
    if((ccCfg & EDMA_TPCC_CCCFG_CHMAP_EXIST_MASK) != 0U)
    {
        for (i = 0U; i < 64U; i++)
        {
            /* All events are one to one mapped with the channels */
            HW_WR_REG32(baseAddr + EDMA_TPCC_DCHMAPN(i), i << 5);
        }
    }

    /* Initialize the DMA Queue Number Registers                            */
    for (count = 0U; count < SOC_EDMA3_NUM_DMACH; count++)
    {
        qnumValue  = HW_RD_REG32(baseAddr + (EDMA_TPCC_DMAQNUMN((count >> 3U))));
        qnumValue &= EDMA3CC_DMAQNUM_CLR(count);
        qnumValue |= EDMA3CC_DMAQNUM_SET(count, queNum);
        HW_WR_REG32(baseAddr + (EDMA_TPCC_DMAQNUMN((count >> 3U))), qnumValue);
    }

    /* FOR TYPE QDMA */
    /* Enable the DMA (0 - 64) channels in the DRAE register                */
    HW_WR_REG32(baseAddr + EDMA_TPCC_QRAEN(gEdmaRegionId), EDMA3_SET_ALL_BITS);

    /* Initialize the QDMA Queue Number Registers                           */
    for (count = 0U; count < SOC_EDMA3_NUM_QDMACH; count++)
    {
        qnumValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_QDMAQNUM);
        qnumValue &= EDMA3CC_QDMAQNUM_CLR(count);
        qnumValue |= EDMA3CC_QDMAQNUM_SET(count, queNum);
        HW_WR_REG32(baseAddr + EDMA_TPCC_QDMAQNUM, qnumValue);
    }
}

void EDMAsetRegion(uint32_t i)
{
    gEdmaRegionId = i;
}

uint32_t EDMA3PeripheralIdGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + EDMA_TPCC_PID));
}

void EDMA3EnableChInShadowReg(uint32_t baseAddr,
                              uint32_t chType,
                              uint32_t chNum)
{
    uint32_t draeValue;
    /* Allocate the DMA/QDMA channel */
    if (EDMA3_CHANNEL_TYPE_DMA == chType)
    {
        /* FOR TYPE EDMA*/
        if (chNum < 32U)
        {
            draeValue = HW_RD_REG32(baseAddr + EDMA_TPCC_DRAEM(gEdmaRegionId));
            /* Enable the DMA channel in the DRAE registers */
            draeValue |= (uint32_t) 0x01U << chNum;
            HW_WR_REG32(baseAddr + EDMA_TPCC_DRAEM(gEdmaRegionId), draeValue);
        }
        else
        {
            draeValue = HW_RD_REG32(baseAddr + EDMA_TPCC_DRAEHM(gEdmaRegionId));

            /* Enable the DMA channel in the DRAEH registers */
            draeValue |= (uint32_t) 0x01U << (chNum - 32U);
            HW_WR_REG32(baseAddr + EDMA_TPCC_DRAEHM(gEdmaRegionId), draeValue);
        }
    }
    else if (EDMA3_CHANNEL_TYPE_QDMA == chType)
    {
        /* FOR TYPE QDMA */
        /* Enable the QDMA channel in the DRAE/DRAEH registers */
        draeValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_QRAEN(gEdmaRegionId));
        draeValue |= (uint32_t) 0x01U << chNum;
        HW_WR_REG32(baseAddr + EDMA_TPCC_QRAEN(gEdmaRegionId), draeValue);
    }
    else
    {
        /*An error will be generated automatically.*/
    }
}

void EDMA3DisableChInShadowReg(uint32_t baseAddr,
                               uint32_t chType,
                               uint32_t chNum)
{
    uint32_t draeValue;
    /* Allocate the DMA/QDMA channel */
    if (EDMA3_CHANNEL_TYPE_DMA == chType)
    {
        /* FOR TYPE EDMA*/
        if (chNum < 32U)
        {
            draeValue = HW_RD_REG32(baseAddr + EDMA_TPCC_DRAEM(gEdmaRegionId));
            /* Enable the DMA channel in the DRAE registers */
            draeValue &= ~((uint32_t) 0x01U << chNum);
            HW_WR_REG32(baseAddr + EDMA_TPCC_DRAEM(gEdmaRegionId), draeValue);
        }
        else
        {
            draeValue = HW_RD_REG32(baseAddr + EDMA_TPCC_DRAEHM(gEdmaRegionId));
            /* Enable the DMA channel in the DRAEH registers */
            draeValue &= ~((uint32_t) 0x01U << (chNum - 32U));
            HW_WR_REG32(baseAddr + EDMA_TPCC_DRAEHM(gEdmaRegionId), draeValue);
        }
    }
    else if (EDMA3_CHANNEL_TYPE_QDMA == chType)
    {
        /* FOR TYPE QDMA */
        draeValue = HW_RD_REG32(baseAddr + EDMA_TPCC_QRAEN(gEdmaRegionId));
        /* Enable the QDMA channel in the DRAE/DRAEH registers */
        draeValue &= ~((uint32_t) 0x01U) << chNum;
        HW_WR_REG32(baseAddr + EDMA_TPCC_QRAEN(gEdmaRegionId), draeValue);
    }
    else
    {
        /*An error will be generated automatically.*/
    }
}

void EDMA3ChannelToParamMap(uint32_t baseAddr,
                            uint32_t channel,
                            uint32_t paramSet)

{
    uint32_t ccCfg = HW_RD_REG32(baseAddr + EDMA_TPCC_CCCFG);
    if((ccCfg & EDMA_TPCC_CCCFG_CHMAP_EXIST_MASK) != 0U)
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_DCHMAPN(channel), paramSet << 5U);
    }
}

void EDMA3MapChToEvtQ(uint32_t baseAddr,
                      uint32_t chType,
                      uint32_t chNum,
                      uint32_t evtQNum)
{
    uint32_t qnumValue;
    if (EDMA3_CHANNEL_TYPE_DMA == chType)
    {
        /* Associate DMA Channel to Event Queue                             */
        qnumValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_DMAQNUMN(chNum >> 3U));
        qnumValue &= EDMA3CC_DMAQNUM_CLR(chNum);
        qnumValue |= EDMA3CC_DMAQNUM_SET(chNum, evtQNum);
        HW_WR_REG32(baseAddr + EDMA_TPCC_DMAQNUMN(chNum >> 3U), qnumValue);
    }
    else if (EDMA3_CHANNEL_TYPE_QDMA == chType)
    {
        /* Associate QDMA Channel to Event Queue                            */
        qnumValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_QDMAQNUM);
        qnumValue &= EDMA3CC_QDMAQNUM_CLR(chNum);
        qnumValue |= EDMA3CC_QDMAQNUM_SET(chNum, evtQNum);
        HW_WR_REG32(baseAddr + EDMA_TPCC_QDMAQNUM, qnumValue);
    }
    else
    {
        /*An error will be generated automatically.*/
    }
}

void EDMA3UnmapChToEvtQ(uint32_t baseAddr,
                        uint32_t chType,
                        uint32_t chNum)
{
    uint32_t qnumValue;
    if (EDMA3_CHANNEL_TYPE_DMA == chType)
    {
        /* Unmap DMA Channel to Event Queue                                */
        qnumValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_DMAQNUMN(chNum >> 3U));
        qnumValue &= EDMA3CC_DMAQNUM_CLR(chNum);
        HW_WR_REG32(baseAddr + EDMA_TPCC_DMAQNUMN(chNum >> 3U), qnumValue);
    }
    else if (EDMA3_CHANNEL_TYPE_QDMA == chType)
    {
        /* Unmap QDMA Channel to Event Queue                               */
        qnumValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_QDMAQNUM);
        qnumValue &= EDMA3CC_QDMAQNUM_CLR(chNum);
        HW_WR_REG32(baseAddr + EDMA_TPCC_QDMAQNUM, qnumValue);
    }
    else
    {
        /*An error will be generated automatically.*/
    }
}

void EDMA3MapQdmaChToPaRAM(uint32_t        baseAddr,
                           uint32_t        chNum,
                           const uint32_t *paRAMId)
{
    uint32_t qchmapValue;
    /* Map Parameter RAM Set Number for specified channelId             */
    qchmapValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_QCHMAPN(chNum));
    qchmapValue &= EDMA3CC_QCHMAP_PAENTRY_CLR;
    qchmapValue |= (uint32_t) EDMA3CC_QCHMAP_PAENTRY_SET(*paRAMId);
    HW_WR_REG32(baseAddr + EDMA_TPCC_QCHMAPN(chNum), qchmapValue);
}

uint32_t EDMA3GetMappedPaRAM(uint32_t baseAddr,
                             uint32_t chNum,
                             uint32_t chType,
                             uint32_t *paramId)
{
    uint32_t retVal = FALSE;
    if ((EDMA3_CHANNEL_TYPE_DMA == chType) &&
        (chNum <= SOC_EDMA3_NUM_DMACH))
    {
        uint32_t ccCfg = HW_RD_REG32(baseAddr + EDMA_TPCC_CCCFG);
        if((ccCfg & EDMA_TPCC_CCCFG_CHMAP_EXIST_MASK) != 0U)
        {
            *paramId = chNum;
        }
        else
        {
            *paramId = HW_RD_FIELD32(baseAddr + EDMA_TPCC_DCHMAPN(chNum),
                                    EDMA_TPCC_DCHMAPN_PAENTRY);
        }
        retVal = TRUE;
    }
    else if ((EDMA3_CHANNEL_TYPE_QDMA == chType) &&
             (chNum <= SOC_EDMA3_NUM_QDMACH))
    {
        *paramId = HW_RD_FIELD32(baseAddr + EDMA_TPCC_QCHMAPN(chNum),
                                EDMA_TPCC_QCHMAPN_PAENTRY);
        retVal = TRUE;
    }
    else
    {
        /*An error will be generated automatically.*/
    }
    return retVal;
}

void EDMA3SetQdmaTrigWord(uint32_t baseAddr,
                          uint32_t chNum,
                          uint32_t trigWord)
{
    uint32_t qchmapValue;
    qchmapValue = HW_RD_REG32(baseAddr + EDMA_TPCC_QCHMAPN(chNum));
    /* Clear QDMA Trigger word value */
    qchmapValue &= EDMA3CC_QCHMAP_TRWORD_CLR;
    /* Set the Trigger Word */
    qchmapValue |= EDMA3CC_QCHMAP_TRWORD_SET(trigWord);
    HW_WR_REG32(baseAddr + EDMA_TPCC_QCHMAPN(chNum), qchmapValue);
}

void EDMA3ClrMissEvt(uint32_t baseAddr, uint32_t chNum)
{
    if (chNum < 32U)
    {
        /*clear SECR to clean any previous NULL request */
        HW_WR_REG32(baseAddr + EDMA_TPCC_SECR_RN(
                        gEdmaRegionId), (uint32_t) 0x01U << chNum);

        /*clear EMCR to clean any previous NULL request */
        HW_WR_REG32(baseAddr + EDMA_TPCC_EMCR, (uint32_t) 0x01U << chNum);
    }
    else
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_SECRH_RN(gEdmaRegionId),
                    (uint32_t) 0x01U << (chNum - 32U));
        /*clear EMCRH to clean any previous NULL request */
        HW_WR_REG32(baseAddr + EDMA_TPCC_EMCRH, (uint32_t) 0x01U << (chNum - 32U));
    }
}

void EDMA3QdmaClrMissEvt(uint32_t baseAddr, uint32_t chNum)
{
    /*clear SECR to clean any previous NULL request  */
    HW_WR_REG32(baseAddr + EDMA_TPCC_QSECR_RN(
                    gEdmaRegionId), (uint32_t) 0x01U << chNum);

    /*clear EMCR to clean any previous NULL request  */
    HW_WR_REG32(baseAddr + EDMA_TPCC_QEMCR, (uint32_t) 0x01U << chNum);
}

void EDMA3ClrCCErr(uint32_t baseAddr, uint32_t flags)
{
    /* (CCERRCLR) - clear channel controller error register */
    HW_WR_REG32(baseAddr + EDMA_TPCC_CCERRCLR, flags);
}

void EDMA3SetEvt(uint32_t baseAddr, uint32_t chNum)
{
    if (chNum < 32U)
    {
        /* (ESR) - set corresponding bit to set a event */
        HW_WR_REG32(baseAddr + EDMA_TPCC_ESR_RN(
                        gEdmaRegionId), (uint32_t) 0x01U << chNum);
    }
    else
    {
        /* (ESRH) - set corresponding bit to set a event */
        HW_WR_REG32(baseAddr + EDMA_TPCC_ESRH_RN(gEdmaRegionId),
                    (uint32_t) 0x01U << (chNum - 32U));
    }
}

void EDMA3ClrEvt(uint32_t baseAddr, uint32_t chNum)
{
    if (chNum < 32U)
    {
        /* (ECR) - set corresponding bit to clear a event */
        HW_WR_REG32(baseAddr + EDMA_TPCC_ECR_RN(
                        gEdmaRegionId), (uint32_t) 0x01U << chNum);
    }
    else
    {
        /* (ECRH) - set corresponding bit to clear a event */
        HW_WR_REG32(baseAddr + EDMA_TPCC_ECRH_RN(gEdmaRegionId),
                    (uint32_t) 0x01U << (chNum - 32U));
    }
}

void EDMA3EnableDmaEvt(uint32_t baseAddr, uint32_t chNum)
{
    if (chNum < 32U)
    {
        /* (EESR) - set corresponding bit to enable DMA event */
        HW_WR_REG32(baseAddr + EDMA_TPCC_EESR_RN(
                        gEdmaRegionId), (uint32_t) 0x01U << chNum);
    }
    else
    {
        /* (EESRH) - set corresponding bit to enable DMA event */
        HW_WR_REG32(baseAddr + EDMA_TPCC_EESRH_RN(gEdmaRegionId),
                    (uint32_t) 0x01U << (chNum - 32U));
    }
}

void EDMA3DisableDmaEvt(uint32_t baseAddr, uint32_t chNum)
{
    if (chNum < 32U)
    {
        /* (EECR) - set corresponding bit to disable event */
        HW_WR_REG32(baseAddr + EDMA_TPCC_EECR_RN(
                        gEdmaRegionId), (uint32_t) 0x01U << chNum);
    }
    else
    {
        /* (EECRH) - set corresponding bit to disable event */
        HW_WR_REG32(baseAddr + EDMA_TPCC_EECRH_RN(
                        gEdmaRegionId), (uint32_t) 0x01U << (chNum - 32U));
    }
}

void EDMA3EnableQdmaEvt(uint32_t baseAddr, uint32_t chNum)
{
    /* (QEESR) - set corresponding bit to enable QDMA event                 */
    HW_WR_REG32(baseAddr + EDMA_TPCC_QEESR_RN(
                    gEdmaRegionId), (uint32_t) 0x01U << chNum);
}

void EDMA3DisableQdmaEvt(uint32_t baseAddr, uint32_t chNum)
{
    /* (QEESR) - set corresponding bit to enable QDMA event                 */
    HW_WR_REG32(baseAddr + EDMA_TPCC_QEECR_RN(
                    gEdmaRegionId), (uint32_t) 0x01U << chNum);
}

uint32_t EDMA3GetCCErrStatus(uint32_t baseAddr)
{
    uint32_t intrStatusVal = 0;
    intrStatusVal = HW_RD_REG32(baseAddr + EDMA_TPCC_CCERR);

    return intrStatusVal;
}

uint32_t EDMA3GetIntrStatus(uint32_t baseAddr)
{
    uint32_t intrStatusVal = 0;

    intrStatusVal = HW_RD_REG32(baseAddr + EDMA_TPCC_IPR_RN(gEdmaRegionId));

    return intrStatusVal;
}

uint32_t EDMA3IntrStatusHighGet(uint32_t baseAddr)
{
    uint32_t intrStatusVal = 0;

    intrStatusVal = HW_RD_REG32(baseAddr + EDMA_TPCC_IPRH_RN(gEdmaRegionId));

    return intrStatusVal;
}

uint32_t EDMA3GetErrIntrStatus(uint32_t baseAddr)
{
    uint32_t intrStatusVal = 0;

    intrStatusVal = HW_RD_REG32(baseAddr + EDMA_TPCC_EMR);

    return intrStatusVal;
}

uint32_t EDMA3ErrIntrHighStatusGet(uint32_t baseAddr)
{
    uint32_t intrStatusVal = 0;

    intrStatusVal = HW_RD_REG32(baseAddr + EDMA_TPCC_EMRH);

    return intrStatusVal;
}

uint32_t EDMA3QdmaGetErrIntrStatus(uint32_t baseAddr)
{
    uint32_t intrStatusVal = 0;
    intrStatusVal = HW_RD_REG32(baseAddr + EDMA_TPCC_QEMR);

    return intrStatusVal;
}

void EDMA3EnableEvtIntr(uint32_t baseAddr, uint32_t chNum)
{
    if (chNum < 32U)
    {
        /*  Interrupt Enable Set Register (IESR) */
        HW_WR_REG32(baseAddr + EDMA_TPCC_IESR_RN(
                        gEdmaRegionId), (uint32_t) 0x01U << chNum);
    }
    else
    {
        /*  Interrupt Enable Set Register (IESRH) */
        HW_WR_REG32(baseAddr + EDMA_TPCC_IESRH_RN(gEdmaRegionId),
                    (uint32_t) 0x01U << (chNum - 32U));
    }
}

void EDMA3DisableEvtIntr(uint32_t baseAddr, uint32_t chNum)
{
    if (chNum < 32U)
    {
        /* Interrupt Enable Clear Register (IECR) */
        HW_WR_REG32(baseAddr + EDMA_TPCC_IECR_RN(
                        gEdmaRegionId), (uint32_t) 0x01U << chNum);
    }
    else
    {
        /* Interrupt Enable Clear Register (IECRH) */
        HW_WR_REG32(baseAddr + EDMA_TPCC_IECRH_RN(gEdmaRegionId),
                    (uint32_t) 0x01U << (chNum - 32U));
    }
}

void EDMA3ClrIntr(uint32_t baseAddr, uint32_t value)
{
    if (value < 32U)
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_ICR_RN(
                        gEdmaRegionId), (uint32_t) 1U << value);
    }
    else
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_ICRH_RN(gEdmaRegionId), (uint32_t) 1U <<
                    (value - 32U));
    }
}

void EDMA3GetPaRAM(uint32_t           baseAddr,
                   uint32_t           paRAMId,
                   EDMA3CCPaRAMEntry *currPaRAM)
{
    uint32_t  i = 0;
    uint32_t sr;
    uint32_t *ds = (uint32_t *) currPaRAM;

    sr = baseAddr + EDMA_TPCC_OPT(paRAMId);

    for (i = 0; i < EDMA3CC_PARAM_ENTRY_FIELDS; i++)
    {
        *ds = HW_RD_REG32(sr);
        ds++;
        sr+= (uint32_t)sizeof(uint32_t);
    }
}

void EDMA3QdmaGetPaRAM(uint32_t           baseAddr,
                       uint32_t           paRAMId,
                       EDMA3CCPaRAMEntry *currPaRAM)
{
    uint32_t  i = 0;
    uint32_t *ds     = (uint32_t *) currPaRAM;
    uint32_t  sr     = baseAddr + EDMA_TPCC_OPT(paRAMId);

    for (i = 0; i < EDMA3CC_PARAM_ENTRY_FIELDS; i++)
    {
        *ds = HW_RD_REG32(sr);
        ds++;
        sr+= (uint32_t)sizeof(uint32_t);
    }
}

void EDMA3SetPaRAM(uint32_t           baseAddr,
                   uint32_t           paRAMId,
                   EDMA3CCPaRAMEntry *newPaRAM)
{
    uint32_t           i  = 0;
    uint32_t          *sr = (uint32_t *) newPaRAM;
    volatile uint32_t  ds;
    uint32_t           dsAddr =baseAddr + EDMA_TPCC_OPT(paRAMId);

    ds = (uint32_t ) (dsAddr);

    for (i = 0; i < EDMA3CC_PARAM_ENTRY_FIELDS; i++)
    {
        HW_WR_REG32(ds, *sr);
        ds+= (uint32_t)sizeof(uint32_t);
        sr++;
    }
}

void EDMA3QdmaSetPaRAM(uint32_t           baseAddr,
                       uint32_t           paRAMId,
                       EDMA3CCPaRAMEntry *newPaRAM)
{
    uint32_t  i  = 0;
    uint32_t *sr = (uint32_t *) newPaRAM;
    uint32_t  ds;
    uint32_t  dsAddr =baseAddr + EDMA_TPCC_OPT(paRAMId);

    ds = (uint32_t ) (dsAddr);

    for (i = 0; i < EDMA3CC_PARAM_ENTRY_FIELDS; i++)
    {
        HW_WR_REG32(ds, *sr);
        ds+= (uint32_t)sizeof(uint32_t);
        sr++;
    }
}

void EDMA3QdmaSetPaRAMEntry(uint32_t baseAddr,
                            uint32_t paRAMId,
                            uint32_t paRAMEntry,
                            uint32_t newPaRAMEntryVal)
{
    if (paRAMEntry <= EDMA3CC_PARAM_ENTRY_CCNT)
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_OPT(paRAMId) +
                    (paRAMEntry * 0x04U), newPaRAMEntryVal);
    }
}

uint32_t EDMA3QdmaGetPaRAMEntry(uint32_t baseAddr,
                                uint32_t paRAMId,
                                uint32_t paRAMEntry)
{
    uint32_t paRAMEntryVal = 0;
    if (paRAMEntry <= EDMA3CC_PARAM_ENTRY_CCNT)
    {
        paRAMEntryVal = HW_RD_REG32(baseAddr + EDMA_TPCC_OPT(paRAMId) +
                                    (paRAMEntry * 0x04U));
    }
    return (paRAMEntryVal);
}

uint32_t EDMA3RequestChannel(uint32_t baseAddr,
                             uint32_t chType,
                             uint32_t chNum,
                             uint32_t tccNum,
                             uint32_t evtQNum)
{
    uint32_t optValue, paramId;
    uint32_t retVal = FALSE;
    if (chNum < SOC_EDMA3_NUM_DMACH)
    {
        /* Enable the DMA channel in the enabled in the shadow region
         * specific register
         */
        EDMA3EnableChInShadowReg(baseAddr, chType, chNum);

        EDMA3MapChToEvtQ(baseAddr, chType, chNum, evtQNum);
        if (EDMA3_CHANNEL_TYPE_DMA == chType)
        {
            /* Interrupt channel nums are < 32 */
            if (tccNum < EDMA3_NUM_TCC)
            {
                /* Enable the Event Interrupt                             */
                EDMA3EnableEvtIntr(baseAddr, tccNum);
                retVal = (uint32_t) TRUE;
            }
            if (EDMA3GetMappedPaRAM(baseAddr, chNum, chType, &paramId) == TRUE)
            {
                optValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_OPT(paramId));
                optValue &= EDMA3CC_OPT_TCC_CLR;
                optValue |= EDMA3CC_OPT_TCC_SET(tccNum);
                HW_WR_REG32(baseAddr + EDMA_TPCC_OPT(paramId), optValue);
            }
        }
        else if (EDMA3_CHANNEL_TYPE_QDMA == chType)
        {
            /* Interrupt channel nums are < 8 */
            if (tccNum < EDMA3_NUM_TCC)
            {
                /* Enable the Event Interrupt                             */
                EDMA3EnableEvtIntr(baseAddr, tccNum);
                retVal = (uint32_t) TRUE;
            }
            if (EDMA3GetMappedPaRAM(baseAddr, chNum, chType, &paramId) == TRUE)
            {
                optValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_OPT(chNum));
                optValue &= EDMA3CC_OPT_TCC_CLR;
                optValue |= EDMA3CC_OPT_TCC_SET(tccNum);
                HW_WR_REG32(baseAddr + EDMA_TPCC_OPT(chNum), optValue);
            }
        }
        else
        {
            /*An error will be generated automatically.*/
        }
    }
    return retVal;
}

uint32_t EDMA3FreeChannel(uint32_t baseAddr,
                          uint32_t chType,
                          uint32_t chNum,
                          uint32_t trigMode,
                          uint32_t tccNum,
                          uint32_t evtQNum)
{
    uint32_t retVal = FALSE;
    if (chNum < SOC_EDMA3_NUM_DMACH)
    {
        EDMA3DisableTransfer(baseAddr, chNum, trigMode);
        /* Disable the DMA channel in the shadow region specific register
         */
        EDMA3DisableChInShadowReg(baseAddr, chType, chNum);

        EDMA3UnmapChToEvtQ(baseAddr, chType, chNum);
        if (EDMA3_CHANNEL_TYPE_DMA == chType)
        {
            /* Interrupt channel nums are < 32 */
            if (tccNum < SOC_EDMA3_NUM_DMACH)
            {
                /* Disable the DMA Event Interrupt                            */
                EDMA3DisableEvtIntr(baseAddr, chNum);
                retVal = (uint32_t) TRUE;
            }
        }
        else if (EDMA3_CHANNEL_TYPE_QDMA == chType)
        {
            /* Interrupt channel nums are < 8 */
            if (tccNum < SOC_EDMA3_NUM_QDMACH)
            {
                /* Disable the QDMA Event Interrupt                           */
                EDMA3DisableEvtIntr(baseAddr, chNum);
                retVal = (uint32_t) TRUE;
            }
        }
        else
        {
            /*An error will be generated automatically.*/
        }
    }
    return retVal;
}

uint32_t EDMA3EnableTransfer(uint32_t baseAddr,
                             uint32_t chNum,
                             uint32_t trigMode)
{
    uint32_t retVal = FALSE;
    switch (trigMode)
    {
        case EDMA3_TRIG_MODE_MANUAL:
            if (chNum < SOC_EDMA3_NUM_DMACH)
            {
                EDMA3SetEvt(baseAddr, chNum);
                retVal = (uint32_t) TRUE;
            }
            break;

        case EDMA3_TRIG_MODE_QDMA:
            if (chNum < SOC_EDMA3_NUM_QDMACH)
            {
                EDMA3EnableQdmaEvt(baseAddr, chNum);
                retVal = (uint32_t) TRUE;
            }
            break;

        case EDMA3_TRIG_MODE_EVENT:
            if (chNum < SOC_EDMA3_NUM_DMACH)
            {
                /*clear SECR & EMCR to clean any previous NULL request    */
                EDMA3ClrMissEvt(baseAddr, chNum);

                /* Set EESR to enable event                               */
                EDMA3EnableDmaEvt(baseAddr, chNum);
                retVal = (uint32_t) TRUE;
            }
            break;

        default:
            retVal = (uint32_t) FALSE;
            break;
    }
    return retVal;
}

uint32_t EDMA3DisableTransfer(uint32_t baseAddr,
                              uint32_t chNum,
                              uint32_t trigMode)
{
    uint32_t retVal = FALSE;
    switch (trigMode)
    {
        case EDMA3_TRIG_MODE_MANUAL:
            if (chNum < SOC_EDMA3_NUM_DMACH)
            {
                EDMA3ClrEvt(baseAddr, chNum);
                retVal = (uint32_t) TRUE;
            }
            break;

        case EDMA3_TRIG_MODE_QDMA:
            if (chNum < SOC_EDMA3_NUM_QDMACH)
            {
                EDMA3DisableQdmaEvt(baseAddr, chNum);
                retVal = (uint32_t) TRUE;
            }
            break;

        case EDMA3_TRIG_MODE_EVENT:
            if (chNum < SOC_EDMA3_NUM_DMACH)
            {
                /*clear SECR & EMCR to clean any previous NULL request    */
                EDMA3ClrMissEvt(baseAddr, chNum);

                /* Set EESR to enable event                               */
                EDMA3DisableDmaEvt(baseAddr, chNum);
                retVal = (uint32_t) TRUE;
            }
            break;

        default:
            retVal = (uint32_t) FALSE;
            break;
    }
    return retVal;
}

void EDMA3ClearErrorBits(uint32_t baseAddr,
                         uint32_t chNum,
                         uint32_t evtQNum)
{
    if (chNum < SOC_EDMA3_NUM_DMACH)
    {
        if (chNum < 32U)
        {
            HW_WR_REG32(baseAddr + EDMA_TPCC_EECR_RN(
                            gEdmaRegionId), (uint32_t) 0x01U << chNum);
            /* Write to EMCR to clear the corresponding EMR bit */
            HW_WR_REG32(baseAddr + EDMA_TPCC_EMCR, (uint32_t) 0x01U << chNum);
            /* Clears the SER */
            HW_WR_REG32(baseAddr + EDMA_TPCC_SECR_RN(
                            gEdmaRegionId), (uint32_t) 0x01U << chNum);
        }
        else
        {
            HW_WR_REG32(baseAddr +
                        EDMA_TPCC_EECRH_RN(gEdmaRegionId), (uint32_t) 0x01U <<
                        (chNum - 32U));
            /* Write to EMCR to clear the corresponding EMR bit */
            HW_WR_REG32(baseAddr + EDMA_TPCC_EMCRH, (uint32_t) 0x01U <<
                        (chNum - 32U));
            /* Clears the SER */
            HW_WR_REG32(baseAddr +
                        EDMA_TPCC_SECRH_RN(gEdmaRegionId), (uint32_t) 0x01U <<
                        (chNum - 32U));
        }
    }

    /* Clear the global CC Error Register */
    if (0U == evtQNum)
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_CCERRCLR,
                    EDMA_TPCC_CCERRCLR_QTHRXCD0_MASK |
                    EDMA_TPCC_CCERRCLR_TCERR_MASK);
    }
    else if (1U == evtQNum)
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_CCERRCLR,
                    EDMA_TPCC_CCERRCLR_QTHRXCD1_MASK |
                    EDMA_TPCC_CCERRCLR_TCERR_MASK);
    }
    else if (2U == evtQNum)
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_CCERRCLR,
                    EDMA_TPCC_CCERRCLR_QTHRXCD2_MASK |
                    EDMA_TPCC_CCERRCLR_TCERR_MASK);
    }
    else if (3U == evtQNum)
    {
        HW_WR_REG32(baseAddr + EDMA_TPCC_CCERRCLR,
                    EDMA_TPCC_CCERRCLR_QTHRXCD3_MASK |
                    EDMA_TPCC_CCERRCLR_TCERR_MASK);
    }
    else
    {
        /*Error will be generated automatically*/
    }
}

void EDMA3Deinit(uint32_t baseAddr, uint32_t queNum)
{
    uint32_t count = 0;
    uint32_t qnumValue;

    /* Disable the DMA (0 - 62) channels in the DRAE register */
    HW_WR_REG32(baseAddr + EDMA_TPCC_DRAEM(
                    gEdmaRegionId), EDMA3_CLR_ALL_BITS);
    HW_WR_REG32(baseAddr + EDMA_TPCC_DRAEHM(
                    gEdmaRegionId), EDMA3_CLR_ALL_BITS);

    EDMA3ClrCCErr(baseAddr, EDMA3CC_CLR_TCCERR);

    /* Clear the Event miss Registers                      */
    HW_WR_REG32(baseAddr + EDMA_TPCC_EMCR, EDMA3_SET_ALL_BITS);
    HW_WR_REG32(baseAddr + EDMA_TPCC_EMCRH, EDMA3_SET_ALL_BITS);

    /* Clear CCERR register */
    HW_WR_REG32(baseAddr + EDMA_TPCC_CCERRCLR, EDMA3_SET_ALL_BITS);

    /* Disable and clear channel interrupts for all dma channels */
    for (count = 0; count < EDMA3_NUM_TCC; count++)
    {
        EDMA3DisableEvtIntr(baseAddr, count);
        EDMA3ClrIntr(baseAddr, count);
    }
    /* Disable and clear channel interrupts for all qdma channels */
    for (count = 0; count < SOC_EDMA3_NUM_QDMACH; count++)
    {
         EDMA3DisableQdmaEvt(baseAddr, count);
         EDMA3QdmaClrMissEvt(baseAddr, count);
    }

    /* Deinitialize the Queue Number Registers */
    for (count = 0; count < SOC_EDMA3_NUM_DMACH; count++)
    {
        qnumValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_DMAQNUMN((count >> 3U)));
        qnumValue &= EDMA3CC_DMAQNUM_CLR(count);
        HW_WR_REG32(baseAddr + EDMA_TPCC_DMAQNUMN((count >> 3U)), qnumValue);
    }

    for (count = 0; count < SOC_EDMA3_NUM_QDMACH; count++)
    {
        qnumValue  = HW_RD_REG32(baseAddr + EDMA_TPCC_QDMAQNUM);
        qnumValue &= EDMA3CC_QDMAQNUM_CLR(count);
        HW_WR_REG32(baseAddr + EDMA_TPCC_QDMAQNUM, qnumValue);
    }
}

void EDMA3ChainChannel(uint32_t baseAddr,
                       uint32_t chId1,
                       uint32_t chId2,
                       uint32_t chainOptions)
{
    EDMA3CCPaRAMEntry *currPaRAM     = NULL;
    uint32_t           currPaRAMAddr = baseAddr + EDMA_TPCC_OPT(chId1);
    uint32_t           optVal;
    uintptr_t          optAddr;

    /* Get param set for the channel Id passed*/
    currPaRAM = (EDMA3CCPaRAMEntry *) (currPaRAMAddr);

    optAddr    = (uintptr_t) &currPaRAM->opt;
    optVal = HW_RD_REG32((uint32_t) optAddr);
    optVal &= ~(EDMA3_OPT_TCCHEN_MASK | EDMA3_OPT_ITCCHEN_MASK |
               EDMA3_OPT_TCINTEN_MASK | EDMA3_OPT_ITCINTEN_MASK);
    optVal |= chainOptions;
    optVal &= ~EDMA_TPCC_OPT_TCC_MASK;
    optVal |= (chId2 << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK;
    HW_WR_REG32((uint32_t) optAddr, optVal);
}

void EDMA3LinkChannel(uint32_t baseAddr,
                      uint32_t paRAMId1,
                      uint32_t paRAMId2)
{
    EDMA3CCPaRAMEntry *currPaRAM1;
    EDMA3CCPaRAMEntry *currPaRAM2;
    uint32_t           optVal1, optVal2;
    uint32_t           currPaRAMAddr1 = baseAddr + EDMA_TPCC_OPT(paRAMId1);
    uint32_t           currPaRAMAddr2 = baseAddr + EDMA_TPCC_OPT(paRAMId2);
    uintptr_t          lnkAddr;

    /* Get param set for the paRAMId1 passed*/
    currPaRAM1 = (EDMA3CCPaRAMEntry *) (currPaRAMAddr1);

    /* Update the Link field with lch2 PaRAM set */
    lnkAddr = (uintptr_t) &currPaRAM1->linkAddr;
    HW_WR_REG16(lnkAddr,
        (uint16_t) ((baseAddr + EDMA_TPCC_OPT(paRAMId2)) & (uint16_t) 0x0FFFF));

    /* Get param set for the paRAMId2 passed*/
    currPaRAM2 = (EDMA3CCPaRAMEntry *) (currPaRAMAddr2);

    /*Updated TCC value of param2 with that of param1*/
    optVal1 = HW_RD_REG32((uint32_t) &currPaRAM1->opt);
    optVal2 = HW_RD_REG32((uint32_t) &currPaRAM2->opt);
    optVal2 &= ~EDMA_TPCC_OPT_TCC_MASK;
    optVal2 |= optVal1 & EDMA_TPCC_OPT_TCC_MASK;
    HW_WR_REG32((uint32_t) &currPaRAM2->opt, optVal2);
}

/********************************* End of file ******************************/
