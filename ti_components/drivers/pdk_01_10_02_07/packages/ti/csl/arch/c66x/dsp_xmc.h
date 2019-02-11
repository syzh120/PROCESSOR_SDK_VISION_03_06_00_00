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
 *  \ingroup CSL_ARCH_C66X
 *  \defgroup CSL_ARCH_C66X_XMC XMC
 *
 *  @{
 */
/**
 *  \file     dsp_xmc.h
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of Extended Memory Controller (XMC)
 *            in the C66x DSP subsytems.
 *            This also include related macro definitions.
 *            All APIs should be called with interrupts disabled to
 *            ensure coherency.
 */

#ifndef DSP_XMC_H_
#define DSP_XMC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define DSPXMC_NUM_SEGMENTS             (16U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  enum dspxmcSegSize_t
 *  \brief Enums for Segment Size in XMC configuration
 */
typedef enum dspxmcSegSize
{
    DSPXMC_SEGSZ_DISABLED = 0x00U,
    DSPXMC_SEGSZ_4KB      = 0x0BU,
    DSPXMC_SEGSZ_8KB      = 0x0CU,
    DSPXMC_SEGSZ_16KB     = 0x0DU,
    DSPXMC_SEGSZ_32KB     = 0x0EU,
    DSPXMC_SEGSZ_64KB     = 0x0FU,
    DSPXMC_SEGSZ_128KB    = 0x10U,
    DSPXMC_SEGSZ_256KB    = 0x11U,
    DSPXMC_SEGSZ_512KB    = 0x12U,
    DSPXMC_SEGSZ_1MB      = 0x13U,
    DSPXMC_SEGSZ_2MB      = 0x14U,
    DSPXMC_SEGSZ_4MB      = 0x15U,
    DSPXMC_SEGSZ_8MB      = 0x16U,
    DSPXMC_SEGSZ_16MB     = 0x17U,
    DSPXMC_SEGSZ_32MB     = 0x18U,
    DSPXMC_SEGSZ_64MB     = 0x19U,
    DSPXMC_SEGSZ_128MB    = 0x1AU,
    DSPXMC_SEGSZ_256MB    = 0x1BU,
    DSPXMC_SEGSZ_512MB    = 0x1CU,
    DSPXMC_SEGSZ_1GB      = 0x1DU,
    DSPXMC_SEGSZ_2GB      = 0x1EU,
    DSPXMC_SEGSZ_4GB      = 0x1FU
} dspxmcSegSize_t;

/**
 * \brief  Enum to permissions mask for MPAX (memory protection and address
 *         extension) registers in XMC
 */
typedef enum dspxmcAccessPerms
{
    DSPXMC_ALLOW_UR = XMPAXL_UR_MASK,
    /**< Enable bit User mode Read access */
    DSPXMC_ALLOW_UW = XMPAXL_UW_MASK,
    /**< Enable bit User mode Write access */
    DSPXMC_ALLOW_UX = XMPAXL_UX_MASK,
    /**< Enable bit User mode Execute access */
    DSPXMC_ALLOW_SR = XMPAXL_SR_MASK,
    /**< Enable bit Supervisor mode Read access */
    DSPXMC_ALLOW_SW = XMPAXL_SW_MASK,
    /**< Enable bit Supervisor mode Write access */
    DSPXMC_ALLOW_SX = XMPAXL_SX_MASK
                      /**< Enable bit Supervisor mode Execute access */
} dspxmcAccessPerms_t;

/**
 *  \brief This structure is returned by DSPXMCGetFaultStatus APIs
 */
typedef struct dspxmcFaultStatus
{
    uint32_t localAccess;
    /**< Access was made locally by DSP - Value is TRUE/FALSE */
    uint32_t userModeExec;
    /**< USER mode EXECUTE permissions - Value is TRUE/FALSE */
    uint32_t userModeWrite;
    /**< USER mode WRITE permissions - Value is TRUE/FALSE */
    uint32_t userModeRead;
    /**< USER mode READ permissions - Value is TRUE/FALSE */
    uint32_t supvModeExec;
    /**< SUPERVISOR mode EXECUTE permissions - Value is TRUE/FALSE */
    uint32_t supvModeWrite;
    /**< SUPERVISOR mode WRITE permissions - Value is TRUE/FALSE */
    uint32_t supvModeRead;
    /**< SUPERVISOR mode READ permissions - Value is TRUE/FALSE */
    uint32_t fid;
    /**< ID of initiator who caused the fault - Valid if localAccess = FALSE */
} dspxmcFaultStatus_t;

/**
 *  \brief This structure is returned by DSPXMCGetFaultStatus APIs
 */
typedef struct dspxmcPfxAnalysisStat
{
    uint32_t trigInst;
    /**< Value which written to XPFCMD before updating counter values */
    uint32_t sentCount;
    /**< Prefetch transactions sent */
    uint32_t cancelledCount;
    /**< Prefetch transactions cancelled */
    uint32_t hitCount;
    /**< Hit count for Prefetch transactions */
    uint32_t missCount;
    /**< Miss count for Prefetch transactions */
} dspxmcPfxAnalysisStat_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
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
 * \return  status        Success of the window configuration
 */
int32_t DSPXMCSetMPAXSegment(uint32_t baseAddress,
                             uint32_t segmentId,
                             uint32_t segmentSize,
                             uint32_t inpBAddress,
                             uint32_t repAddressL,
                             uint32_t repAddressH,
                             uint32_t permsFieldVal);

/**
 * \brief   Get the fault location as reported by XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \return  faultAddr     Address where the first fault was generated
 */
uint32_t DSPXMCGetFaultAddr(uint32_t baseAddress);

/**
 * \brief   Get the fault status as reported by XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param  faultStatus    Will be updated as per XMPFSR
 *                        Structure of type #dspxmcFaultStatus_t
 *
 * \return  status        Always returns STW_OK
 */
int32_t DSPXMCGetFaultStatus(uint32_t             baseAddress,
                             dspxmcFaultStatus_t *faultStatus);

/**
 * \brief   Clear the fault registers for location and status in the XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \return  status        Always returns STW_OK
 */
int32_t DSPXMCClearFaultRegs(uint32_t baseAddress);

/**
 * \brief   Set prefetch request priority for XMC
 *          TBD: Planning to remove - usage information is not clear
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param   priority      Priority from 0(highest) to 7(lowest)
 *
 * \return  status        Always returns STW_OK
 */
int32_t DSPXMCSetPrefetchPriority(uint32_t baseAddress, uint32_t priority);

/**
 * \brief   Invalidate Prefetch buffers in XMC
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \return  status        Always returns STW_OK
 */
int32_t DSPXMCInvalidatePrefetch(uint32_t baseAddress);

/**
 * \brief   Reset analysis counter
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \return  status        Always returns STW_OK
 */
int32_t DSPXMCResetAnalysisCtr(uint32_t baseAddress);

/**
 * \brief   Enable analysis counter
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param   triggerInst   Value from 0-3, this will be returned along with
 *                        read of analysis counters
 *
 * \return  status        Always returns STW_OK
 */
int32_t DSPXMCEnablePfxAnalysisCtr(uint32_t baseAddress, uint32_t triggerInst);

/**
 * \brief   Get status analysis counter
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                          (SOC_DSP_XMC_CTRL_BASE)
 *
 * \param   pfxStat       Will be filled with data from analysis counters
 *                        Will be struct of type #dspxmcPfxAnalysisStat_t
 *
 * \return  status        Always returns STW_OK
 */
int32_t DSPXMCGetPFxAnalysisCtrStat(uint32_t                 baseAddress,
                                    dspxmcPfxAnalysisStat_t *pfxStat);

#ifdef __cplusplus
}
#endif

#endif /* DSP_XMC_H_ */
 /** @} */
