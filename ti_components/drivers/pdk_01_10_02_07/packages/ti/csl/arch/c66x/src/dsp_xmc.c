/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     dsp_xmc.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of DSP L1/L2 memory controller.
 *            This include APIs for cache usage and DSP memory protection
 *            unit usage.
 *            This also include related macro definitions.
 *            All APIs should be called with interrupts disabled to
 *            ensure coherency.
 */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DSPXMC_RADDRL_RSHIFT (4U)
#define DSPXMC_RADDRH_LSHIFT (28U)
#define DSPXMC_RADDRH_MASK   (0xFU)

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *
 * \brief   Configure the specified MPAX segment
 *          Input address (inpBAddress - 32bit) is the virtual address
 *          used by the DSP.
 *          Replacement address (repAddressH/L - 36bit) is the physical address
 *          to which the virtual address maps to.
 *          "Physical" refers only to address map at C66x CorePac boundary
 *          and does not account translation done by any memory
 *          controller outside the DSP.
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param   segmentId     Segment ID to use - 16 segments are supported.
 *                        Any value greater than 15 will be considered as 15.
 *
 * \param   segmentSize   Use enum #dspxmcSegSize_t
 *
 * \param   inpBAddress   32bit input address as per C66x native address space.
 *                        Should be aligned to segmentSize.
 *                        This will be the .
 *
 * \param   repAddressL   Lower 32bits of replacement address (36bit)
 *                        Should be aligned to segmentSize.
 *                        For address 0x1_2345_6789, this value must be
 *                        0x2345_6789.
 *
 * \param   repAddressH   Upper 4bits of replacement address (36bit)
 *                        For address 0x1_2345_6789, this value must be
 *                        0x1. In most cases, this will be 0x0.
 *
 * \param   permsFieldVal Bitfield specifying access rights to the segment
 *                        Create this by bit-wise "OR" ing of enums specified
 *                        in  #dspxmcAccessPerms_t
 *
 * \return  status        Always returns STW_SOK indicating success
 */
int32_t DSPXMCSetMPAXSegment(uint32_t baseAddress,
                             uint32_t segmentId,
                             uint32_t segmentSize,
                             uint32_t inpBAddress,
                             uint32_t repAddressL,
                             uint32_t repAddressH,
                             uint32_t permsFieldVal)
{
    uint32_t regVal;
    uint32_t permsMask = (XMPAXL_UX_MASK |
                          XMPAXL_UW_MASK |
                          XMPAXL_UR_MASK |
                          XMPAXL_SX_MASK |
                          XMPAXL_SW_MASK |
                          XMPAXL_SR_MASK);

    /* Clear fields which we are going to modify */
    regVal  = HW_RD_REG32(baseAddress + XMPAXL(segmentId));
    regVal &= ~XMPAXL_RADDR_MASK;
    regVal &= ~permsMask;

    /* Set value for RADDR field */
    regVal     |= ((repAddressL >> DSPXMC_RADDRL_RSHIFT) & XMPAXL_RADDR_MASK);
    repAddressH = (repAddressH & DSPXMC_RADDRH_MASK);
    regVal     |= ((repAddressH << DSPXMC_RADDRH_LSHIFT) & XMPAXL_RADDR_MASK);

    /* Set value for permissions included in permsMask */
    permsFieldVal = (permsFieldVal & permsMask);
    regVal       |= permsFieldVal;

    /* Write into XMPAXL */
    HW_WR_REG32(baseAddress + XMPAXL(segmentId), regVal);

    regVal  = 0;
    regVal |= (segmentSize & XMPAXH_SEGSZ_MASK);
    regVal |= (inpBAddress & XMPAXH_BADDR_MASK);
    /* Write into XMPAXH */
    HW_WR_REG32(baseAddress + XMPAXH(segmentId), regVal);

    return STW_SOK;
}

/**
 * \brief   Get the fault location as reported by XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \return  faultAddr     Address where the first fault was generated
 */
uint32_t DSPXMCGetFaultAddr(uint32_t baseAddress)
{
    return HW_RD_REG32(baseAddress + XMPFAR);
}

/**
 * \brief   Get the fault status as reported by XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param  faultStatus    Will be updated as per XMPFSR
 *                        Structure of type #dspxmcFaultStatus_t
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPXMCGetFaultStatus(uint32_t             baseAddress,
                             dspxmcFaultStatus_t *faultStatus)
{
    uint32_t regVal = HW_RD_REG32(baseAddress + XMPFSR);

    faultStatus->userModeExec  = regVal & 0x01U;
    faultStatus->userModeRead  = regVal & 0x02U;
    faultStatus->userModeWrite = regVal & 0x04U;
    faultStatus->supvModeExec  = regVal & 0x08U;
    faultStatus->supvModeWrite = regVal & 0x10U;
    faultStatus->supvModeRead  = regVal & 0x20U;
    faultStatus->localAccess   = regVal & XMPFSR_LOCAL_MASK;
    faultStatus->fid           = regVal & 0xFEU;

    return STW_SOK;
}

/**
 * \brief   Clear the fault registers for location and status in the XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPXMCClearFaultRegs(uint32_t baseAddress)
{
    HW_WR_REG32((baseAddress + XMPFCR), 0x1U);
    return STW_SOK;
}

/**
 * \brief   Set prefetch request priority for XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param   priority      Priority from 0(highest) to 7(lowest)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPXMCSetPrefetchPriority(uint32_t baseAddress, uint32_t priority)
{
    HW_WR_FIELD32((baseAddress + MDMAARBX), MDMAARBX_PRI, priority);
    return STW_SOK;
}

/**
 * \brief   Invalidate Prefetch buffers in XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPXMCInvalidatePrefetch(uint32_t baseAddress)
{
    HW_WR_FIELD32((baseAddress + XPFCMD), XPFCMD_INV, 0x1U);

    /* Dummy read to ensure completion of command */
    HW_RD_REG32((baseAddress + XPFACS));
    return STW_SOK;
}

/**
 * \brief   Reset analysis counter
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPXMCResetAnalysisCtr(uint32_t baseAddress)
{
    HW_WR_FIELD32((baseAddress + XPFCMD), XPFCMD_ACRST, 0x1U);

    /* Dummy read to ensure completion of command */
    HW_RD_REG32((baseAddress + XPFACS));
    return STW_SOK;
}

/**
 * \brief   Enable analysis counter
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param   triggerInst   Value from 0-3, this will be returned along with
 *                        read of analysis counters
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPXMCEnablePfxAnalysisCtr(uint32_t baseAddress, uint32_t triggerInst)
{
    /* Set value to be copied to XPFACS.ACEN */
    HW_WR_FIELD32((baseAddress + XPFCMD), XPFCMD_ACEN, triggerInst);
    /* Send command to be update XPFACS and XPFAC0-3  */
    HW_WR_FIELD32((baseAddress + XPFCMD), XPFCMD_ACENL, 0x1U);

    /* Dummy read to ensure completion of command */
    HW_RD_REG32((baseAddress + XPFACS));
    return STW_SOK;
}

/**
 * \brief   Get status analysis counter
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param   pfxStat       Will be filled with data from analysis counters
 *                        Will be struct of type #dspxmcPfxAnalysisStat_t
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPXMCGetPFxAnalysisCtrStat(uint32_t                 baseAddress,
                                    dspxmcPfxAnalysisStat_t *pfxStat)
{
    pfxStat->trigInst =
        HW_RD_FIELD32((baseAddress + XPFACS), XPFACS_ACEN);
    pfxStat->sentCount =
        HW_RD_FIELD32((baseAddress + XPFAC0), XPFAC0_SENT);
    pfxStat->cancelledCount =
        HW_RD_FIELD32((baseAddress + XPFAC1), XPFAC1_CANCELED);
    pfxStat->hitCount =
        HW_RD_FIELD32((baseAddress + XPFAC2), XPFAC2_HIT);
    pfxStat->missCount =
        HW_RD_FIELD32((baseAddress + XPFAC3), XPFAC3_MISS);

    return STW_SOK;
}
