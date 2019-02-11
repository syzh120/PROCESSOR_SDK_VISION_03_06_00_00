/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   mcasp.c
 *
 *  \brief  McASP APIs.
 *
 *   This file contains the device abstraction layer APIs for McASP.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_mcasp.h>
#include <ti/csl/csl_mcasp.h>

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void McASPTxReset(uint32_t baseAddr)
{
    HW_WR_REG32(baseAddr + MCASP_GBLCTLX, MCASP_RESET);
}

void McASPRxReset(uint32_t baseAddr)
{
    HW_WR_REG32(baseAddr + MCASP_GBLCTLR, MCASP_RESET);
}

void McASPWriteFifoEnable(uint32_t baseAddr, uint32_t numTxSer,
                          uint32_t minWdPerSer)
{
    HW_WR_REG32(
        baseAddr + MCASP_WFIFOCTL,
        numTxSer | ((minWdPerSer * numTxSer) << MCASP_WFIFOCTL_WNUMEVT_SHIFT));

    /* The configuration is done. now set the enable bit */
    HW_WR_FIELD32(baseAddr + MCASP_WFIFOCTL, MCASP_WFIFOCTL_WENA, 1U);
}

void McASPReadFifoEnable(uint32_t baseAddr, uint32_t numRxSer,
                         uint32_t minWdPerSer)
{
    HW_WR_REG32(
        baseAddr + MCASP_RFIFOCTL,
        numRxSer | ((minWdPerSer * numRxSer) << MCASP_RFIFOCTL_RNUMEVT_SHIFT));

    /* The configuration is done. now set the enable bit */
    HW_WR_FIELD32(baseAddr + MCASP_RFIFOCTL, MCASP_RFIFOCTL_RENA, 1U);
}

void McASPTxFmtMaskSet(uint32_t baseAddr, uint32_t mask)
{
    HW_WR_REG32(baseAddr + MCASP_TXMASK, mask);
}

void McASPRxFmtMaskSet(uint32_t baseAddr, uint32_t mask)
{
    HW_WR_REG32(baseAddr + MCASP_RXMASK, mask);
}

void McASPTxFmtSet(uint32_t baseAddr, uint32_t formatVal)
{
    HW_WR_REG32(baseAddr + MCASP_TXFMT, formatVal);
}

void McASPRxFmtSet(uint32_t baseAddr, uint32_t formatVal)
{
    HW_WR_REG32(baseAddr + MCASP_RXFMT, formatVal);
}

void McASPTxFmtI2SSet(uint32_t baseAddr, uint32_t wordSize,
                      uint32_t slotSize, uint32_t txMode)
{
    /* Set the mask assuming integer format */
    McASPTxFmtMaskSet(baseAddr, ((uint32_t) 1U << wordSize) - 1U);

    /* Set the transmit format unit for I2S */
    McASPTxFmtSet(
        baseAddr,
        ((uint32_t) MCASP_TX_PAD_WITH_0 | (uint32_t) MCASP_TX_BITSTREAM_MSB_FIRST |
         MCASP_TX_SYNC_DELAY_1BIT |
         ((wordSize >> 2U) & MCASP_TXFMT_XROT_MASK) |
         (((slotSize / 2U) - 1U) << MCASP_TXFMT_XSSZ_SHIFT) | txMode));
}

void McASPRxFmtI2SSet(uint32_t baseAddr, uint32_t wordSize,
                      uint32_t slotSize, uint32_t rxMode)
{
    /* Set the mask assuming integer format */
    McASPRxFmtMaskSet(baseAddr, ((uint32_t) 1U << wordSize) - 1U);

    /* Set the receive format unit for I2S */
    McASPRxFmtSet(
        baseAddr,
        ((uint32_t) MCASP_RX_PAD_WITH_0 | (uint32_t) MCASP_RX_BITSTREAM_MSB_FIRST |
         MCASP_RX_SYNC_DELAY_1BIT |
         (((slotSize - wordSize) >> 2U) & MCASP_RXFMT_RROT_MASK) |
         (((slotSize / 2U) - 1U) << MCASP_RXFMT_RSSZ_SHIFT) | rxMode));
}

void McASPTxFrameSyncCfg(uint32_t baseAddr, uint32_t fsMode,
                         uint32_t fsWidth, uint32_t fsSetting)
{
    HW_WR_REG32(
        baseAddr + MCASP_TXFMCTL,
        (fsMode << MCASP_TXFMCTL_XMOD_SHIFT) |
        (fsWidth << MCASP_TXFMCTL_FXWID_SHIFT) |
        fsSetting);
}

void McASPRxFrameSyncCfg(uint32_t baseAddr, uint32_t fsMode,
                         uint32_t fsWidth, uint32_t fsSetting)
{
    HW_WR_REG32(
        baseAddr + MCASP_RXFMCTL,
        (fsMode << MCASP_RXFMCTL_RMOD_SHIFT) |
        (fsWidth << MCASP_RXFMCTL_FRWID_SHIFT) |
        fsSetting);
}

void McASPTxClkCfg(uint32_t baseAddr, uint32_t clkSrc,
                   uint32_t mixClkDiv, uint32_t auxClkDiv)
{
    uint32_t regValAClk = 0U, regValAHClk = 0U;

    regValAClk  = HW_RD_REG32(baseAddr + MCASP_ACLKXCTL);
    regValAClk &= ~((uint32_t) MCASP_ACLKXCTL_CLKXM_MASK | (uint32_t) MCASP_ACLKXCTL_CLKXDIV_MASK);
    HW_WR_REG32(baseAddr + MCASP_ACLKXCTL, regValAClk);

    regValAHClk  = HW_RD_REG32(baseAddr + MCASP_AHCLKXCTL);
    regValAHClk &=
        ~((uint32_t) MCASP_AHCLKXCTL_HCLKXM_MASK | (uint32_t) MCASP_AHCLKXCTL_HCLKXDIV_MASK);
    HW_WR_REG32(baseAddr + MCASP_AHCLKXCTL, regValAHClk);

    /* Set the clock source to chose internal/external with clkdiv */
    regValAClk  = HW_RD_REG32(baseAddr + MCASP_ACLKXCTL);
    regValAClk |= ((clkSrc & MCASP_ACLKXCTL_CLKXM_MASK) | mixClkDiv);
    HW_WR_REG32(baseAddr + MCASP_ACLKXCTL, regValAClk);

    regValAHClk  = HW_RD_REG32(baseAddr + MCASP_AHCLKXCTL);
    regValAHClk |= ((clkSrc & MCASP_AHCLKXCTL_HCLKXM_MASK) | auxClkDiv);
    HW_WR_REG32(baseAddr + MCASP_AHCLKXCTL, regValAHClk);
}

void McASPRxClkCfg(uint32_t baseAddr, uint32_t clkSrc,
                   uint32_t mixClkDiv, uint32_t auxClkDiv)
{
    uint32_t regValAClk = 0U, regValAHClk = 0U;

    regValAClk  = HW_RD_REG32(baseAddr + MCASP_ACLKRCTL);
    regValAClk &= ~((uint32_t) MCASP_ACLKRCTL_CLKRM_MASK | (uint32_t) MCASP_ACLKRCTL_CLKRDIV_MASK);
    HW_WR_REG32(baseAddr + MCASP_ACLKRCTL, regValAClk);

    regValAHClk  = HW_RD_REG32(baseAddr + MCASP_AHCLKRCTL);
    regValAHClk &=
        ~((uint32_t) MCASP_AHCLKRCTL_HCLKRM_MASK | (uint32_t) MCASP_AHCLKRCTL_HCLKRDIV_MASK);
    HW_WR_REG32(baseAddr + MCASP_AHCLKRCTL, regValAHClk);

    /* Set the clock source to chose internal/external with clkdiv */
    regValAClk  = HW_RD_REG32(baseAddr + MCASP_ACLKRCTL);
    regValAClk |= ((clkSrc & MCASP_ACLKRCTL_CLKRM_MASK) | mixClkDiv);
    HW_WR_REG32(baseAddr + MCASP_ACLKRCTL, regValAClk);

    regValAHClk  = HW_RD_REG32(baseAddr + MCASP_AHCLKRCTL);
    regValAHClk |= ((clkSrc & MCASP_AHCLKRCTL_HCLKRM_MASK) | auxClkDiv);
    HW_WR_REG32(baseAddr + MCASP_AHCLKRCTL, regValAHClk);
}

void McASPTxClkPolaritySet(uint32_t baseAddr, uint32_t polarity)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_ACLKXCTL,
        MCASP_ACLKXCTL_CLKXP,
        polarity >> MCASP_ACLKXCTL_CLKXP_SHIFT);
}

void McASPTxClkDivSet(uint32_t baseAddr, uint32_t clkDiv)
{
    HW_WR_FIELD32(baseAddr + MCASP_ACLKXCTL,
        MCASP_ACLKXCTL_CLKXDIV,
        clkDiv);
}

void McASPRxClkPolaritySet(uint32_t baseAddr, uint32_t polarity)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_ACLKRCTL,
        MCASP_ACLKRCTL_CLKRP,
        polarity >> MCASP_ACLKRCTL_CLKRP_SHIFT);
}

void McASPTxHFClkPolaritySet(uint32_t baseAddr, uint32_t polarity)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_AHCLKXCTL,
        MCASP_AHCLKXCTL_HCLKXP,
        polarity >> MCASP_AHCLKXCTL_HCLKXP_SHIFT);
}

void McASPRxHFClkPolaritySet(uint32_t baseAddr, uint32_t polarity)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_AHCLKRCTL,
        MCASP_AHCLKRCTL_HCLKRP,
        polarity >> MCASP_AHCLKRCTL_HCLKRP_SHIFT);
}

void McASPTxRxClkSyncEnable(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_ACLKXCTL,
        MCASP_ACLKXCTL_ASYNC,
        MCASP_ACLKXCTL_ASYNC_SYNC);
}

void McASPTxRxClkSyncDisable(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_ACLKXCTL,
        MCASP_ACLKXCTL_ASYNC,
        MCASP_ACLKXCTL_ASYNC_ASYNC);
}

void McASPSerializerTxSet(uint32_t baseAddr, uint32_t serNum)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_SRCTL(serNum),
        MCASP_XRSRCTL0_SRMOD,
        MCASP_XRSRCTL0_SRMOD_XMT);
}

void McASPSerializerRxSet(uint32_t baseAddr, uint32_t serNum)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_SRCTL(serNum),
        MCASP_XRSRCTL0_SRMOD,
        MCASP_XRSRCTL0_SRMOD_RCV);
}

void McASPSerializerInactivate(uint32_t baseAddr, uint32_t serNum)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_SRCTL(serNum),
        MCASP_XRSRCTL0_SRMOD,
        MCASP_XRSRCTL0_SRMOD_INACTIVE);
}

void McASPPinGPIOSet(uint32_t baseAddr, uint32_t pinMask)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_PFUNC);

    regVal |= pinMask;

    HW_WR_REG32(baseAddr + MCASP_PFUNC, regVal);
}

void McASPPinMcASPSet(uint32_t baseAddr, uint32_t pinMask)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_PFUNC);

    regVal &= ~pinMask;

    HW_WR_REG32(baseAddr + MCASP_PFUNC, regVal);
}

void McASPPinDirOutputSet(uint32_t baseAddr, uint32_t pinMask)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_PDIR);

    regVal |= pinMask;

    HW_WR_REG32(baseAddr + MCASP_PDIR, regVal);
}

void McASPPinDirInputSet(uint32_t baseAddr, uint32_t pinMask)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_PDIR);

    regVal &= ~pinMask;

    HW_WR_REG32(baseAddr + MCASP_PDIR, regVal);
}

void McASPTxTimeSlotSet(uint32_t baseAddr, uint32_t slotMask)
{
    HW_WR_REG32(baseAddr + MCASP_TXTDM, slotMask);
}

void McASPRxTimeSlotSet(uint32_t baseAddr, uint32_t slotMask)
{
    HW_WR_REG32(baseAddr + MCASP_RXTDM, slotMask);
}

void McASPTxClkCheckConfig(uint32_t baseAddr, uint32_t clkDiv,
                           uint8_t boundMin, uint8_t boundMax)
{
    HW_WR_REG32(
        baseAddr + MCASP_TXCLKCHK,
        clkDiv | (((uint32_t) boundMin) << MCASP_TXCLKCHK_XMIN_SHIFT)
        | (((uint32_t) boundMax) << MCASP_TXCLKCHK_XMAX_SHIFT));
}

void McASPRxClkCheckConfig(uint32_t baseAddr, uint32_t clkDiv,
                           uint8_t boundMin, uint8_t boundMax)
{
    HW_WR_REG32(
        baseAddr + MCASP_RXCLKCHK,
        clkDiv | (((uint32_t) boundMin) << MCASP_RXCLKCHK_RMIN_SHIFT)
        | (((uint32_t) boundMax) << MCASP_RXCLKCHK_RMAX_SHIFT));
}

void McASPTxIntEnable(uint32_t baseAddr, uint32_t intMask)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_EVTCTLX);

    regVal |= intMask;

    HW_WR_REG32(baseAddr + MCASP_EVTCTLX, regVal);
}

void McASPRxIntEnable(uint32_t baseAddr, uint32_t intMask)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_EVTCTLR);

    regVal |= intMask;

    HW_WR_REG32(baseAddr + MCASP_EVTCTLR, regVal);
}

void McASPTxSerActivate(uint32_t baseAddr)
{
    uint32_t regVal = 0U;

    HW_WR_REG32(baseAddr + MCASP_TXSTAT, (uint32_t) 0xFFFFU);

    /* Release transmit serializers from reset*/
    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= MCASP_GBLCTL_XSRCLR_MASK;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);
    while((HW_RD_REG32(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XSRCLR_MASK)
          != MCASP_GBLCTL_XSRCLR_MASK)
    {
        /* Do nothing - Busy wait */
    }
}

void McASPRxSerActivate(uint32_t baseAddr)
{
    uint32_t regVal = 0U;

    HW_WR_REG32(baseAddr + MCASP_RXSTAT, (uint32_t) 0xFFFFU);

    /* Release transmit serializers from reset*/
    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= MCASP_GBLCTL_RSRCLR_MASK;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);

    while((HW_RD_REG32(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RSRCLR_MASK)
          != MCASP_GBLCTL_RSRCLR_MASK)
    {
        /* Do nothing - Busy wait */
    }
}

void McASPTxClkStart(uint32_t baseAddr, uint32_t clkSrc)
{
    uint32_t regVal = 0U;

    /* Release the high frequency clock from reset*/
    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= MCASP_GBLCTL_XHCLKRST_MASK;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);

    while((HW_RD_REG32(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XHCLKRST_MASK)
          != MCASP_GBLCTL_XHCLKRST_MASK)
    {
        /* Do nothing - Busy wait */
    }

    if(clkSrc != MCASP_TX_CLK_EXTERNAL)
    {
        /* Release the clock from reset*/
        regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

        regVal |= MCASP_GBLCTL_XCLKRST_MASK;

        HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);
        while((HW_RD_REG32(baseAddr +
                           MCASP_GBLCTL) & MCASP_GBLCTL_XCLKRST_MASK)
              != MCASP_GBLCTL_XCLKRST_MASK)
        {
            /* Do nothing - Busy wait */
        }
    }
}

void McASPRxClkStart(uint32_t baseAddr, uint32_t clkSrc)
{
    uint32_t regVal = 0U;

    /* Release the high frequency clock from reset*/
    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= MCASP_GBLCTL_RHCLKRST_MASK;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);

    while((HW_RD_REG32(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RHCLKRST_MASK)
          != MCASP_GBLCTL_RHCLKRST_MASK)
    {
        /* Do nothing - Busy wait */
    }

    if(clkSrc != MCASP_RX_CLK_EXTERNAL)
    {
        /* Release the clock from reset*/
        regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

        regVal |= MCASP_GBLCTL_RCLKRST_MASK;

        HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);
        while((HW_RD_REG32(baseAddr +
                           MCASP_GBLCTL) & MCASP_GBLCTL_RCLKRST_MASK)
              != MCASP_GBLCTL_RCLKRST_MASK)
        {
            /* Do nothing - Busy wait */
        }
    }
}

void McASPTxEnable(uint32_t baseAddr)
{
    uint32_t regVal = 0U;

    /* Release the Transmit State machine from reset*/
    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= MCASP_GBLCTL_XSMRST_MASK;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);
    while((HW_RD_REG32(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XSMRST_MASK)
          != MCASP_GBLCTL_XSMRST_MASK)
    {
        /* Do nothing - Busy wait */
    }

    /* Release the frame sync generator from reset*/
    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= MCASP_GBLCTL_XFRST_MASK;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);
    while((HW_RD_REG32(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_XFRST_MASK)
          != MCASP_GBLCTL_XFRST_MASK)
    {
        /* Do nothing - Busy wait */
    }
}

void McASPRxEnable(uint32_t baseAddr)
{
    uint32_t regVal = 0U;

    /* Release the Receive State machine from reset*/
    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= MCASP_GBLCTL_RSMRST_MASK;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);
    while((HW_RD_REG32(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RSMRST_MASK)
          != MCASP_GBLCTL_RSMRST_MASK)
    {
        /* Do nothing - Busy wait */
    }

    /* Release the frame sync generator from reset*/
    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= MCASP_GBLCTL_RFRST_MASK;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);
    while((HW_RD_REG32(baseAddr + MCASP_GBLCTL) & MCASP_GBLCTL_RFRST_MASK)
          != MCASP_GBLCTL_RFRST_MASK)
    {
        /* Do nothing - Busy wait */
    }
}

uint32_t McASPRxBufRead(uint32_t baseAddr, uint32_t serNum)
{
    return (HW_RD_REG32(baseAddr + MCASP_RXBUF(serNum)));
}

void McASPTxBufWrite(uint32_t baseAddr, uint32_t serNum,
                     uint32_t data)
{
    HW_WR_REG32(baseAddr + MCASP_TXBUF(serNum), data);
}

uint32_t McASPTxStatusGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_TXSTAT));
}

uint32_t McASPRxStatusGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_RXSTAT));
}

void McASPGlobalCtlReset(uint32_t baseAddr)
{
    HW_WR_REG32(baseAddr + MCASP_GBLCTL, MCASP_RESET);
}

void McASPGlobalCtlSet(uint32_t baseAddr, uint32_t globalCtlVal)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_GBLCTL);

    regVal |= globalCtlVal;

    HW_WR_REG32(baseAddr + MCASP_GBLCTL, regVal);
}

uint32_t McASPGlobalCtlGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_GBLCTL));
}

uint32_t McASPTxGlobalCtlGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_GBLCTLX));
}

uint32_t McASPRxGlobalCtlGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_GBLCTLR));
}

void McASPTxGlobalCtlSet(uint32_t baseAddr, uint32_t txGlobalCtlVal)
{
    HW_WR_REG32(baseAddr + MCASP_GBLCTLX, txGlobalCtlVal);
}

void McASPRxGlobalCtlSet(uint32_t baseAddr, uint32_t rxGlobalCtlVal)
{
    HW_WR_REG32(baseAddr + MCASP_GBLCTLR, rxGlobalCtlVal);
}

void McASPWriteFifoDisable(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_WFIFOCTL,
        MCASP_WFIFOCTL_WENA,
        MCASP_DISABLE);
}

void McASPReadFifoDisable(uint32_t baseAddr)
{
    HW_WR_FIELD32(
        baseAddr + MCASP_RFIFOCTL,
        MCASP_RFIFOCTL_RENA,
        MCASP_DISABLE);
}

uint32_t McASPTxFifoStatusGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_WFIFOSTS));
}

uint32_t McASPRxFifoStatusGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_RFIFOSTS));
}

uint32_t McASPTxIntrStatusGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_EVTCTLX));
}

uint32_t McASPRxIntrStatusGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_EVTCTLR));
}

uint32_t McASPTxFmtMaskGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_TXMASK));
}

uint32_t McASPRxFmtMaskGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_RXMASK));
}

uint32_t McASPTxFmtGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_TXFMT));
}

uint32_t McASPRxFmtGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_RXFMT));
}

uint32_t McASPTxRxFrameSyncRead(uint32_t baseAddr, uint8_t txOrRx)
{
    uint32_t retval;

    if((uint8_t) TX == txOrRx)
    {
        retval = HW_RD_REG32(baseAddr + MCASP_TXFMCTL);
    }
    else
    {
        retval = HW_RD_REG32(baseAddr + MCASP_RXFMCTL);
    }
    return retval;
}

void McASPSerializerSet(uint32_t baseAddr,
                        uint32_t serNum,
                        uint32_t serCtlVal)
{
    HW_WR_REG32(baseAddr + MCASP_SRCTL(serNum), serCtlVal);
}

uint32_t McASPSerializerGet(uint32_t baseAddr, uint32_t serNum)
{
    return (HW_RD_REG32(baseAddr + MCASP_SRCTL(serNum)));
}

uint8_t McASPIsSerializerXmtReady(uint32_t baseAddr, uint32_t serNum)
{
    uint8_t  serailizerXmtStatus;

    uint32_t serializerStatus;

    serializerStatus =
        ((HW_RD_REG32(baseAddr + MCASP_SRCTL(serNum)) &
          MCASP_XRSRCTL0_XRDY_MASK) >> MCASP_XRSRCTL0_XRDY_SHIFT);

    serailizerXmtStatus = (uint8_t) serializerStatus;

    return (serailizerXmtStatus);
}

uint8_t McASPIsSerializerRcvReady(uint32_t baseAddr, uint32_t serNum)
{
    uint8_t  serailizerRcvStatus;

    uint32_t serializerStatus;

    serializerStatus =
        ((HW_RD_REG32(baseAddr + MCASP_SRCTL(serNum)) &
          MCASP_XRSRCTL0_RRDY_MASK) >> MCASP_XRSRCTL0_RRDY_SHIFT);

    serailizerRcvStatus = (uint8_t) serializerStatus;

    return (serailizerRcvStatus);
}

uint32_t McASPTxRxTimeSlotGet(uint32_t baseAddr, uint8_t txOrRx)
{
    uint32_t retval;

    if((uint8_t) TX == txOrRx)
    {
        retval = HW_RD_REG32(baseAddr + MCASP_TXTDM);
    }
    else
    {
        retval = HW_RD_REG32(baseAddr + MCASP_RXTDM);
    }

    return retval;
}

void McASPTxClkCheckRegWrite(uint32_t baseAddr, uint32_t tClkChkVal)
{
    HW_WR_REG32(baseAddr + MCASP_TXCLKCHK, tClkChkVal);
}

uint32_t McASPTxClkCheckRegRead(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_TXCLKCHK));
}

void McASPRxClkCheckRegWrite(uint32_t baseAddr, uint32_t rClkChkVal)
{
    HW_WR_REG32(baseAddr + MCASP_RXCLKCHK, rClkChkVal);
}

uint32_t McASPRxClkCheckRegRead(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_RXCLKCHK));
}

void McASPTxIntDisable(uint32_t baseAddr, uint32_t intMask)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_EVTCTLX);

    regVal &= ~intMask;

    HW_WR_REG32(baseAddr + MCASP_EVTCTLX, regVal);
}

void McASPRxIntDisable(uint32_t baseAddr, uint32_t intMask)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_EVTCTLR);

    regVal &= ~intMask;

    HW_WR_REG32(baseAddr + MCASP_EVTCTLR, regVal);
}

void McASPTxStatusSet(uint32_t baseAddr, uint32_t statusVal)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_TXSTAT);

    regVal |= statusVal;

    HW_WR_REG32(baseAddr + MCASP_TXSTAT, regVal);
}

void McASPRxStatusSet(uint32_t baseAddr, uint32_t statusVal)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_RXSTAT);

    regVal |= statusVal;

    HW_WR_REG32(baseAddr + MCASP_RXSTAT, regVal);
}

void McASPDlbRegWrite(uint32_t baseAddr, uint32_t dlbCtlVal)
{
    HW_WR_REG32(baseAddr + MCASP_LBCTL, dlbCtlVal);
}

uint32_t McASPDlbRegRead(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_LBCTL));
}

void McASPDITModeCtlWrite(uint32_t baseAddr, uint32_t dITModeCtlVal)
{
    uint32_t regVal = 0U;

    regVal = HW_RD_REG32(baseAddr + MCASP_TXDITCTL);

    regVal |= dITModeCtlVal;

    HW_WR_REG32(baseAddr + MCASP_TXDITCTL, regVal);
}

uint32_t McASPDITModeCtlRead(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_TXDITCTL));
}

void McASPDITLeftChanStatusSet(uint32_t baseAddr,
                               uint32_t leftChanNum,
                               uint32_t setVal)
{
    HW_WR_REG32(baseAddr + MCASP_DITCSRA(leftChanNum), setVal);
}

void McASPDITRightChanStatusSet(uint32_t baseAddr,
                                uint32_t rightChanNum,
                                uint32_t setVal)
{
    HW_WR_REG32(baseAddr + MCASP_DITCSRB(rightChanNum), setVal);
}

void McASPDITLeftUserDataRamSet(uint32_t baseAddr,
                                uint32_t leftChanNum,
                                uint32_t setVal)
{
    HW_WR_REG32(baseAddr + MCASP_DITUDRA(leftChanNum), setVal);
}

void McASPDITRightUserDataRamSet(uint32_t baseAddr,
                                 uint32_t rightChanNum,
                                 uint32_t setVal)
{
    HW_WR_REG32(baseAddr + MCASP_DITUDRB(rightChanNum), setVal);
}

uint32_t McASPRxClkPolarityGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_ACLKRCTL));
}

uint32_t McASPTxClkPolarityGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_ACLKXCTL));
}

uint32_t McASPTxClkDivGet(uint32_t baseAddr)
{
    uint32_t clkDiv;
    
    clkDiv = HW_RD_FIELD32(baseAddr + MCASP_ACLKXCTL, 
        MCASP_ACLKXCTL_CLKXDIV);
        
    return clkDiv;
}

uint32_t McASPRxHClkPolarityGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_AHCLKRCTL));
}

uint32_t McASPTxHClkPolarityGet(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + MCASP_AHCLKXCTL));
}

uint16_t McASPCurrTransmitSlot(uint32_t baseAddr)
{
    uint16_t currTxSlot = (uint16_t) MCASP_RESET;

    currTxSlot =
        (uint16_t) (HW_RD_FIELD32(baseAddr + MCASP_TXTDMSLOT,
                                  MCASP_TXTDMSLOT_XSLOTCNT));

    return (currTxSlot);
}

uint16_t McASPCurrReceiveSlot(uint32_t baseAddr)
{
    uint16_t currRxSlot = (uint16_t) MCASP_RESET;

    currRxSlot =
        (uint16_t) (HW_RD_FIELD32(baseAddr + MCASP_RXTDMSLOT,
                                  MCASP_RXTDMSLOT_RSLOTCNT));

    return (currRxSlot);
}

void McASPTxRxDMAEvtCntrlWrite(uint32_t baseAddr,
                               uint8_t  txOrRx,
                               uint32_t txRxDmaCntrlVal)
{
    if((uint8_t) TX == txOrRx)
    {
        HW_WR_REG32(baseAddr + MCASP_XEVTCTL, txRxDmaCntrlVal);
    }
    else
    {
        HW_WR_REG32(baseAddr + MCASP_REVTCTL, txRxDmaCntrlVal);
    }
}

uint32_t McASPTxRxDMAEvtCntrlRead(uint32_t baseAddr,
                                  uint8_t  txOrRx)
{
    uint32_t retval;
    if((uint8_t) TX == txOrRx)
    {
        retval = HW_RD_REG32(baseAddr + MCASP_XEVTCTL);
    }
    else
    {
        retval = HW_RD_REG32(baseAddr + MCASP_XEVTCTL);
    }

    return retval;
}

uint8_t McASPTxErrStatus(uint32_t baseAddr, uint32_t errFlag)
{
    uint8_t errStatus = (uint8_t) FALSE;

    switch(errFlag)
    {
        case MCASP_TX_STAT_ERR:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_TXSTAT,
                               MCASP_TXSTAT_XERR));
            break;
        case MCASP_TX_STAT_DMAERR:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_TXSTAT,
                               MCASP_TXSTAT_XDMAERR));
            break;
        case MCASP_TX_STAT_CLKFAIL:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_TXSTAT,
                               MCASP_TXSTAT_XCKFAIL));
            break;
        case MCASP_TX_STAT_SYNCERR:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_TXSTAT,
                               MCASP_TXSTAT_XSYNCERR));
            break;
        case MCASP_TX_STAT_UNDERRUN:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_TXSTAT,
                               MCASP_TXSTAT_XUNDRN));
            break;
        case MCASP_TX_STAT_DATAREADY:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_TXSTAT,
                               MCASP_TXSTAT_XDATA));
            break;
        default:
            break;
    }
    return (errStatus);
}

uint8_t McASPRxErrStatus(uint32_t baseAddr, uint32_t errFlag)
{
    uint8_t errStatus = (uint8_t) FALSE;
    switch(errFlag)
    {
        case MCASP_RX_STAT_ERR:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_RXSTAT,
                               MCASP_RXSTAT_RERR));
            break;
        case MCASP_RX_STAT_DMAERR:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_RXSTAT,
                               MCASP_RXSTAT_RDMAERR));
            break;
        case MCASP_RX_STAT_CLKFAIL:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_RXSTAT,
                               MCASP_RXSTAT_RCKFAIL));
            break;
        case MCASP_RX_STAT_SYNCERR:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_RXSTAT,
                               MCASP_RXSTAT_RSYNCERR));
            break;
        case MCASP_RX_STAT_OVERRUN:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_RXSTAT,
                               MCASP_RXSTAT_ROVRN));
            break;
        case MCASP_RX_STAT_DATAREADY:
            errStatus =
                (uint8_t) (HW_RD_FIELD32(
                               baseAddr + MCASP_RXSTAT,
                               MCASP_RXSTAT_RDATA));
            break;
        default:
            break;
    }
    return (errStatus);
}

uint8_t McASPGetSmFsRcv(uint32_t baseAddr)
{
    uint32_t smFsRcv = 0U;

    smFsRcv = HW_RD_FIELD32(baseAddr + MCASP_GBLCTLR, MCASP_GBLCTLR_RFRST);

    smFsRcv = smFsRcv << 4U;

    smFsRcv |= HW_RD_FIELD32(baseAddr + MCASP_GBLCTLR, MCASP_GBLCTLR_RSMRST);

    return ((uint8_t) smFsRcv);
}

uint8_t McASPGetSmFsXmt(uint32_t baseAddr)
{
    uint32_t smFsXmt = 0U;

    smFsXmt = HW_RD_FIELD32(baseAddr + MCASP_GBLCTLX, MCASP_GBLCTLX_XFRST);

    smFsXmt = smFsXmt << 4U;

    smFsXmt |= HW_RD_FIELD32(baseAddr + MCASP_GBLCTLX, MCASP_GBLCTLX_XSMRST);

    return ((uint8_t) smFsXmt);
}

void McASPSetPowerIdleConfig(uint32_t baseAddr, uint32_t idleMode)
{
    HW_WR_FIELD32(baseAddr + MCASP_PWRIDLESYSCONFIG,
                  MCASP_PWRIDLESYSCONFIG_IDLE_MODE,
                  idleMode);
}
/* Errata id (i848) : McASP IO pad loopback not functional */
void MCASPDigitalLpbkEnable(uint32_t baseAddr,
                            uint32_t enableLpbk,
                            uint32_t order)
{
    if ((uint32_t) TRUE == enableLpbk)
    {
        /* Enable McASP Digital loop-back */
        HW_WR_FIELD32(baseAddr + MCASP_LBCTL, MCASP_LBCTL_IOLBEN,
                      MCASP_LBCTL_IOLBEN_ENABLE);
        HW_WR_FIELD32(baseAddr + MCASP_LBCTL, MCASP_LBCTL_ORD, order);
        HW_WR_FIELD32(baseAddr + MCASP_LBCTL, MCASP_LBCTL_MODE,
                      MCASP_LBCTL_MODE_XMTCLK);
        HW_WR_FIELD32(baseAddr + MCASP_LBCTL, MCASP_LBCTL_DLBEN,
                      MCASP_LBCTL_DLBEN_ENABLE);
    }
    else
    {
        HW_WR_FIELD32(baseAddr + MCASP_LBCTL, MCASP_LBCTL_ORD, order);
        /* Disable McASP Digital loop-back */
        HW_WR_FIELD32(baseAddr + MCASP_LBCTL, MCASP_LBCTL_DLBEN,
                      MCASP_LBCTL_DLBEN_DISABLE);
    }
}
/****************************** End Of File ***********************************/
