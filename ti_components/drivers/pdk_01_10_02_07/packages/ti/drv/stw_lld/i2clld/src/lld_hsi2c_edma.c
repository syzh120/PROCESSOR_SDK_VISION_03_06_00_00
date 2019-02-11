/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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

#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <lld_hsi2c_edma.h>
#include <ti/drv/stw_lld/i2clld/lld_hsi2c.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/soc.h>

/******************************************************************************
 *                        MACRO DEFINITIONS
 ******************************************************************************/

/* Edma OPT Field specific defines */
#define EDMA3CC_U_BASE      (SOC_EDMA_TPCC_BASE_VIRT)
#define EDMA3CC_IPR_OFFSET  ((uint32_t) EDMA_TPCC_IPR)
#define EDMA3CC_IPRH_OFFSET ((uint32_t) EDMA_TPCC_IPRH)

#define EDMA3CC_ICR_OFFSET  ((uint32_t) EDMA_TPCC_ICR)
#define EDMA3CC_ICRH_OFFSET ((uint32_t) EDMA_TPCC_ICRH)

#define LLD_I2C_EDMA_OPT_SYNCDIM_SHIFT      ((uint32_t) 0x00000002U)
#define LLD_I2C_EDMA_OPT_TCC_MASK           ((uint32_t) 0x0003F000U)
#define LLD_I2C_EDMA_OPT_TCC_SHIFT          ((uint32_t) 0x0000000CU)
#define LLD_I2C_EDMA_OPT_ITCINTEN_SHIFT     ((uint32_t) 0x00000015U)
#define LLD_I2C_EDMA_OPT_TCINTEN_SHIFT      ((uint32_t) 0x00000014U)

#if defined (TI814X_BUILD)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_MASK ((uint32_t) 0x3F000000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_SHIFT ((uint32_t) 0x00000018U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_RESETVAL ((uint32_t) 0x00000000U)

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_MASK ((uint32_t) 0x003F0000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_SHIFT ((uint32_t) 0x00000010U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_RESETVAL ((uint32_t) 0x00000000U)

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK ((uint32_t) 0x00003F00U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT ((uint32_t) 0x00000008U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_RESETVAL ((uint32_t) 0x00000000U)

#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK ((uint32_t) 0x0000003FU)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_SHIFT ((uint32_t) 0x00000000U)
#define CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_RESETVAL ((uint32_t) 0x00000000U)

#define EDMA3_MAX_CROSS_BAR_EVENTS_TI814X  ((uint32_t) 95U)

/*Cross Bar mapped*/
#define LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR    ((uint32_t) 3U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT2_XBAR    ((uint32_t) 4U)

#define LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR    ((uint32_t) 5U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT3_XBAR    ((uint32_t) 6U)

typedef struct  {
    volatile uint32_t DSP_INTMUX[21];
    volatile uint32_t DUCATI_INTMUX[15];
    volatile uint32_t TPCC_EVTMUX[16];
    volatile uint32_t TIMER_EVTCAPT;
    volatile uint32_t GPIO_MUX;
} CSL_IntmuxRegs;

typedef volatile CSL_IntmuxRegs *CSL_IntmuxRegsOvly;

#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#define LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR    ((uint32_t) 3U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT3_XBAR    ((uint32_t) 4U)
#define LLD_I2C_EDMA_CHA_I2CTXEVT4_XBAR    ((uint32_t) 5U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT4_XBAR    ((uint32_t) 6U)
#if defined (SOC_TDA2EX)
#define LLD_I2C_EDMA_CHA_I2CTXEVT5_XBAR    ((uint32_t) 7U)
#define LLD_I2C_EDMA_CHA_I2CRXEVT5_XBAR    ((uint32_t) 8U)
#endif
#endif

static lldHsi2cEdmaCallback callbackFn;

/******************************************************************************
 *                        Local Function Declarations
 ******************************************************************************/
#if defined (TI814X_BUILD)
static uint32_t sampleConfigScr(uint32_t eventNum, uint32_t chanNum);

/**
 * \brief   sampleConfigScr
 *
 * This function configures control config registers for the cross bar events
 * mapped to the EDMA channel.
 *
 * \return  EDMA3_DRV_SOK if success, else error code
 */
static uint32_t sampleConfigScr(uint32_t eventNum, uint32_t chanNum)
{
    uint32_t           retVal        = TRUE;
    uint32_t           scrChanOffset = 0;
    uint32_t           scrRegOffset  = 0;
    uint32_t           xBarEvtNum    = 0;
    CSL_IntmuxRegsOvly scrEvtMux     = (CSL_IntmuxRegsOvly) (0x48140F00U);

    if ((eventNum < EDMA3_MAX_CROSS_BAR_EVENTS_TI814X) &&
        (chanNum < EDMA3_NUM_TCC))
    {
        scrRegOffset  = chanNum / 4U;
        scrChanOffset = chanNum - (scrRegOffset * 4U);
        xBarEvtNum    = (eventNum - EDMA3_NUM_TCC) + 1U;

        switch (scrChanOffset)
        {
            case 0:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    (xBarEvtNum & CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_0_MASK);
                break;
            case 1U:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_SHIFT) &
                     (CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_1_MASK));
                break;
            case 2U:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_SHIFT) &
                     (CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_2_MASK));
                break;
            case 3U:
                scrEvtMux->TPCC_EVTMUX[scrRegOffset] |=
                    ((xBarEvtNum <<
                      CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_SHIFT) &
                     (CSL_INTMUX_TPCC_EVTMUX_TPCCEVT_MUX_3_MASK));
                break;
            default:
                retVal = (UInt32) FALSE;
                break;
        }
    }
    else
    {
        retVal = (UInt32) FALSE;
    }

    return retVal;
}

#endif

void EDMA_callbackFn(void *arg)
{
    uint32_t regVal, tcc, i;
    LLD_hsi2cEdmaStatus i2cEdmaErrStatus = EDMA_TRANSFER_SUCCESS;

#if defined (TI814X_BUILD)
    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPR_OFFSET);
    for (i = 0; i < 4U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR + i;

            tcc += 63U;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICR_OFFSET,
                (uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR + i));
        }
    }

    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPRH_OFFSET);
    for (i = 0; i < 4U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << ((LLD_I2C_EDMA_CHA_I2CTXEVT0 - 32U) + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT0 + i;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICRH_OFFSET,
                (uint32_t) 1U << ((LLD_I2C_EDMA_CHA_I2CTXEVT0 - 32U) + i));
        }
    }
#endif

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPR_OFFSET);
    for (i = 0; i < 6U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT2 + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT2 + i;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICR_OFFSET,
                (uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT2 + i));
        }
    }
    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPR_OFFSET);
    for (i = 0; i < 4U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR + i;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICR_OFFSET,
                (uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR + i));
        }
    }

#endif
#if defined (SOC_TDA3XX)
    regVal = HW_RD_REG32(EDMA3CC_U_BASE + EDMA3CC_IPR_OFFSET);
    for (i = 0; i < 4U; i++)
    {
        if ((uint32_t) 0U !=
            (regVal & ((uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT0 + i))))
        {
            tcc = LLD_I2C_EDMA_CHA_I2CTXEVT0 + i;

            /*I2C LLD EDMA call back function should be called here*/
            callbackFn(tcc, i2cEdmaErrStatus, arg);

            HW_WR_REG32(
                EDMA3CC_U_BASE + EDMA3CC_ICR_OFFSET,
                (uint32_t) 1U << (LLD_I2C_EDMA_CHA_I2CTXEVT0 + i));
        }
    }
#endif
}

LLD_hsi2cEdmaStatus EDMA_requestChannel(hsI2cHandle          handle,
                                        uint32_t            *i2cEventNo,
                                        lldHsi2cEdmaCallback i2cCallback,
                                        void                *edmaParam)
{
#if defined (TI814X_BUILD) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    uint32_t chanNum = 0;
#elif defined (SOC_TDA3XX)
    uint32_t chanNum = *i2cEventNo;
#endif
    LLD_hsi2cEdmaParam *edmaParams    = (LLD_hsi2cEdmaParam *) edmaParam;
    LLD_hsi2cEdmaStatus i2cEdmaStatus = EDMA_TRANSFER_SUCCESS;

    callbackFn = i2cCallback;

#if defined (TI814X_BUILD) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    if (*i2cEventNo >= EDMA3_NUM_TCC)
    {
        switch (*i2cEventNo)
        {
#if defined (TI814X_BUILD)
            case LLD_I2C_EDMA_CHA_I2CTXEVT2:
                chanNum = LLD_I2C_EDMA_CHA_I2CTXEVT2_XBAR;
                break;
            case LLD_I2C_EDMA_CHA_I2CRXEVT2:
                chanNum = LLD_I2C_EDMA_CHA_I2CRXEVT2_XBAR;
                break;
#endif
            case LLD_I2C_EDMA_CHA_I2CTXEVT3:
                chanNum = LLD_I2C_EDMA_CHA_I2CTXEVT3_XBAR;
                break;
            case LLD_I2C_EDMA_CHA_I2CRXEVT3:
                chanNum = LLD_I2C_EDMA_CHA_I2CRXEVT3_XBAR;
                break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            case LLD_I2C_EDMA_CHA_I2CTXEVT4:
                chanNum = LLD_I2C_EDMA_CHA_I2CTXEVT4_XBAR;
                break;
            case LLD_I2C_EDMA_CHA_I2CRXEVT4:
                chanNum = LLD_I2C_EDMA_CHA_I2CRXEVT4_XBAR;
                break;
#if defined (SOC_TDA2EX)
            case LLD_I2C_EDMA_CHA_I2CTXEVT5:
                chanNum = LLD_I2C_EDMA_CHA_I2CTXEVT5_XBAR;
                break;
            case LLD_I2C_EDMA_CHA_I2CRXEVT5:
                chanNum = LLD_I2C_EDMA_CHA_I2CRXEVT5_XBAR;
                break;
#endif
#endif
            default:
                break;
        }

#if defined (TI814X_BUILD)
        if (TRUE == sampleConfigScr(*i2cEventNo, chanNum))
        {
            *i2cEventNo = chanNum;
        }
        else
        {
            i2cEdmaStatus = EDMA_TRANSFER_FAIL;
        }
#else
        *i2cEventNo = chanNum;
#endif
    }
#endif

#if defined (SOC_TDA3XX)
    *i2cEventNo = chanNum;
#endif

    if (TRUE !=
        EDMA3RequestChannel(edmaParams->baseAddr,
                            EDMA3_CHANNEL_TYPE_DMA,
                            *i2cEventNo,
                            *i2cEventNo,
                            edmaParams->eventQueue))
    {
        i2cEdmaStatus = EDMA_TRANSFER_FAIL;
    }

    return i2cEdmaStatus;
}

LLD_hsi2cEdmaStatus EDMA_freeChannel(uint32_t i2cEventNo, void *edmaParam)
{
    LLD_hsi2cEdmaStatus status     = EDMA_TRANSFER_SUCCESS;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;

    if (TRUE !=
        (EDMA3FreeChannel(edmaParams->baseAddr,
                          EDMA3_CHANNEL_TYPE_DMA,
                          i2cEventNo,
                          EDMA3_TRIG_MODE_EVENT,
                          i2cEventNo,
                          edmaParams->eventQueue)))
    {
        status = EDMA_TRANSFER_FAIL;
    }

    return status;
}

LLD_hsi2cEdmaStatus EDMA_disableLogicalChannel(uint32_t tcc, void *edmaParam)
{
    LLD_hsi2cEdmaStatus status     = EDMA_TRANSFER_SUCCESS;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;

    EDMA3DisableDmaEvt(edmaParams->baseAddr, tcc);

    return status;
}

LLD_hsi2cEdmaStatus EDMA_clearErrorBits(uint32_t tcc, void *edmaParam)
{
    LLD_hsi2cEdmaStatus status     = EDMA_TRANSFER_SUCCESS;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;

    EDMA3ClearErrorBits(edmaParams->baseAddr, tcc, edmaParams->eventQueue);

    return status;
}

LLD_hsi2cEdmaStatus EDMA_setPaRAM(const void *srcPtr, const void *dstPtr,
                                  uint32_t rdWrflag,
                                  uint32_t chan, uint32_t bufLen,
                                  void *edmaParam,
                                  uint8_t fifoThreshold)
{
    uint16_t            srcIndex   = 0U;
    uint16_t            dstIndex   = 1U;
    LLD_hsi2cEdmaStatus status     = EDMA_TRANSFER_SUCCESS;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;
    EDMA3CCPaRAMEntry   i2cEdmaParam;

    i2cEdmaParam.opt = 0U;
    if (LLD_HSI2C_WRITE == rdWrflag)
    {
        srcIndex = 1U;
        dstIndex = 0U;

        i2cEdmaParam.srcCIdx  = fifoThreshold;
        i2cEdmaParam.destCIdx = 0U;
    }
    else
    {
        i2cEdmaParam.srcCIdx  = 0U;
        i2cEdmaParam.destCIdx = fifoThreshold;
    }

    i2cEdmaParam.srcAddr  = (uint32_t) srcPtr;
    i2cEdmaParam.destAddr = (uint32_t) dstPtr;
    i2cEdmaParam.aCnt     = 0x1U;

    if (bufLen >= (uint32_t) fifoThreshold)
    {
        i2cEdmaParam.bCnt =
            ((uint16_t) ((uint32_t) 0xFFFFU & (uint32_t) fifoThreshold));
        i2cEdmaParam.cCnt =
            ((uint16_t) ((uint32_t) 0xFFFFU &
                         (bufLen / (uint32_t) fifoThreshold)));
    }
    else
    {
        i2cEdmaParam.bCnt = ((uint16_t) 0xFFFFU & bufLen);
        i2cEdmaParam.cCnt = 1U;
    }

    i2cEdmaParam.srcBIdx  = srcIndex;
    i2cEdmaParam.destBIdx = dstIndex;

    i2cEdmaParam.linkAddr   = 0xFFFFU;
    i2cEdmaParam.bCntReload = 0U;
    i2cEdmaParam.opt       &= (uint32_t) 0xFFFFFFFCU;

    /* FIFO width is 8 bit                                                */
    i2cEdmaParam.opt &= (uint32_t) 0xFFFFF8FFU;

    /* EDMA3_DRV_SYNC_AB                                                  */
    i2cEdmaParam.opt |= (uint32_t) 0x04U;

    /* EDMA3_DRV_OPT_FIELD_TCINTEN                                        */
    i2cEdmaParam.opt |= ((uint32_t) 1U << LLD_I2C_EDMA_OPT_TCINTEN_SHIFT);

    /* update the transfer completion code                                */
    i2cEdmaParam.opt &= (~LLD_I2C_EDMA_OPT_TCC_MASK);
    i2cEdmaParam.opt |= (chan << LLD_I2C_EDMA_OPT_TCC_SHIFT);

    EDMA3SetPaRAM(edmaParams->baseAddr, chan, &i2cEdmaParam);

    return status;
}

LLD_hsi2cEdmaStatus EDMA_enableTransfer(uint32_t chan, void *edmaParam)
{
    LLD_hsi2cEdmaStatus edmaStatus = EDMA_TRANSFER_SUCCESS;
    uint32_t status;
    LLD_hsi2cEdmaParam *edmaParams = (LLD_hsi2cEdmaParam *) edmaParam;

    status = EDMA3EnableTransfer(edmaParams->baseAddr, chan,
                                 EDMA3_TRIG_MODE_EVENT);
    if (FALSE == status)
    {
        edmaStatus = EDMA_TRANSFER_FAIL;
    }
    return edmaStatus;
}

