/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated
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
 *  \file     fwlibl3.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of L3FW.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <fwlibl3.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API will return index for given L3 firewall instance in global
 *          struct #gL3FwInst.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 *
 * \return  index           Index in gL3FWInst structure.
 */
uint32_t FWLIBL3GetInstSummary(uint32_t baseAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
l3fwInstSummary_t gL3FWInst[L3FW_INST_NUM] = L3FW_INST_SUMMARY;
#if defined (SOC_TDA2PX)
#if defined (__ARM_ARCH_7A__)
/**
 * \brief  Structure contains information about mreqDomain register.
 */
typedef struct
{
	uint32_t offset;
	/* Register offset in the control module */
	uint32_t shift;
	/* Bit shift at which the mreqdomain can be configured */
} mreqDomainRegisterInfo;

mreqDomainRegisterInfo gDomainInfoTbl[CSL_MREQDOMAIN_INITIATOR_MAX_INITIATOR] =
{
	{ CTRL_CORE_MREQDOMAIN_EXP1, 0U},/* MREQDOMAIN_P1500 */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 3U},/* MREQDOMAIN_RESERVED1_FACEDETECT */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 6U},/* MREQDOMAIN_DSP1_CFG */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 9U},/* MREQDOMAIN_DSS */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 12U},/* MREQDOMAIN_IVAHD */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 15U},/* MREQDOMAIN_RESERVED2_ISS */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 18U},/* MREQDOMAIN_IPU1 */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 21U},/* MREQDOMAIN_GPU_P1 */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 24U},/* MREQDOMAIN_DSP2_CFG */
	{ CTRL_CORE_MREQDOMAIN_EXP1, 27U},/* MREQDOMAIN_IPU2 */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 0U},/* MREQDOMAIN_MMC1 */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 3U},/* MREQDOMAIN_MMC2 */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 6U},/* MREQDOMAIN_EVE1_TC0 */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 9U},/* MREQDOMAIN_EVE2_TC0 */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 12U},/* MREQDOMAIN_USB1 */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 18U},/* MREQDOMAIN_USB2 */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 21U},/* MREQDOMAIN_USB3 */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 24U},/* MREQDOMAIN_SATA */
	{ CTRL_CORE_MREQDOMAIN_EXP2, 27U},/* MREQDOMAIN_EVE3_TC0 */
	{ CTRL_CORE_MREQDOMAIN_EXP3, 0U},/* MREQDOMAIN_EVE4_TC0 */
	{ CTRL_CORE_MREQDOMAIN_EXP3, 6U},/* MREQDOMAIN_BB2D */
	{ CTRL_CORE_MREQDOMAIN_EXP3, 9U},/* MREQDOMAIN_PRUSS1_PRU0 */
	{ CTRL_CORE_MREQDOMAIN_EXP3, 12U},/* MREQDOMAIN_PRUSS2_PRU0 */
	{ CTRL_CORE_MREQDOMAIN_EXP3, 15U},/* MREQDOMAIN_VIP1_P1 */
	{ CTRL_CORE_MREQDOMAIN_EXP3, 18U},/* MREQDOMAIN_VIP2_P1 */
	{ CTRL_CORE_MREQDOMAIN_EXP3, 21U},/* MREQDOMAIN_VIP3_P1 */
	{ CTRL_CORE_MREQDOMAIN_EXP3, 24U},/* MREQDOMAIN_USB4 */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 0U},/* MREQDOMAIN_MLB */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 6U},/* MREQDOMAIN_PCIESS1 */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 9U},/* MREQDOMAIN_PCIESS2 */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 12U},/* MREQDOMAIN_MMU1 */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 15U},/* MREQDOMAIN_MMU2 */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 18U},/* MREQDOMAIN_GMACSW */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 21U},/* MREQDOMAIN_VPE_P1 */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 24U},/* MREQDOMAIN_DSP1_MDMA */
	{ CTRL_CORE_MREQDOMAIN_EXP4, 27U},/* MREQDOMAIN_DSP2_MDMA */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 0U},/* MREQDOMAIN_VIP1_P2 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 3U},/* MREQDOMAIN_VIP2_P2 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 6U},/* MREQDOMAIN_VIP3_P2 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 9U},/* MREQDOMAIN_VPE_P2 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 12U},/* MREQDOMAIN_GPU_P2 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 15U},/* MREQDOMAIN_PRUSS1_PRU1 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 18U},/* MREQDOMAIN_PRUSS2_PRU1 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 21U},/* MREQDOMAIN_EVE1_TC1 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 24U},/* MREQDOMAIN_EVE2_TC1 */
	{ CTRL_CORE_MREQDOMAIN_EXP5, 27U}/* MREQDOMAIN_EVE3_TC1 */
};

#endif
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#if defined (SOC_TDA2PX)
#if defined (__ARM_ARCH_7A__)
uint32_t FWLIBL3MReqDomainReadDomainId(uint32_t initiator)
{
	uint32_t regVal, domainVal = 0xFFU;
	uint32_t regAddr;
    uint32_t mask;

	if (initiator < CSL_MREQDOMAIN_INITIATOR_MAX_INITIATOR)
	{
		regAddr = gDomainInfoTbl[initiator].offset +
                            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE;
		regVal = HW_RD_REG32(regAddr);
        mask   = (uint32_t) 0x7U << gDomainInfoTbl[initiator].shift;
		domainVal = (regVal & mask) >> gDomainInfoTbl[initiator].shift;
	}

	return domainVal;
}

int32_t FWLIBL3MReqDomainWriteDomainId(uint32_t initiator, uint32_t domainId)
{
	uint32_t regVal;
	uint32_t regAddr;
	int32_t retVal = STW_SOK;
	uint32_t offset;
    uint32_t mask;

	if (initiator < CSL_MREQDOMAIN_INITIATOR_MAX_INITIATOR)
	{
		regAddr = gDomainInfoTbl[initiator].offset +
                            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE;
		regVal = HW_RD_REG32(regAddr);
        mask   = (uint32_t) 0x7U << gDomainInfoTbl[initiator].shift;
		regVal = regVal & (~(mask));
		regVal = regVal | ((domainId & 0x7U) << gDomainInfoTbl[initiator].shift);
		offset = gDomainInfoTbl[initiator].offset;
		if (0U == FW_setMReqDomainId(offset, regVal))
        {
            retVal = STW_SOK;
        }
        else
        {
            retVal = STW_EFAIL;
        }
	}
    else
    {
        retVal = STW_EFAIL;
    }

	return retVal;
}
#endif
#endif

int32_t FWLIBL3ConfigRegion(uint32_t                        baseAddr,
                            const l3fwRegionConfigParams_t *regionParams,
                            uint32_t                        numOfMasters,
                            const l3fwMasterList_t         *masterList)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;
    l3fwRegionConfigParams_t regionConfigParams;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    /* Configure region */
    if (STW_SOK == status)
    {
        if (0U == regionParams->regionId)
        {
            regionConfigParams.regionId         = regionParams->regionId;
            regionConfigParams.regionPermission =
                regionParams->regionPermission;
            regionConfigParams.targetBaseAddr  = regionParams->targetBaseAddr;
            regionConfigParams.regionStartAddr = 0;
            regionConfigParams.regionEndAddr   = 0;
            L3FWSetRegionParams(baseAddr, &regionConfigParams);
        }
        else if ((gL3FWInst[instIndex].fwNumRegions >
                  regionParams->regionId) &&
                 (regionParams->regionEndAddr > regionParams->regionStartAddr))
        {
            regionConfigParams.regionId        = regionParams->regionId;
            regionConfigParams.targetBaseAddr  = regionParams->targetBaseAddr;
            regionConfigParams.regionStartAddr =
                regionParams->regionStartAddr;
            regionConfigParams.regionEndAddr    = regionParams->regionEndAddr;
            regionConfigParams.regionPermission =
                regionParams->regionPermission;
            L3FWSetRegionParams(baseAddr, &regionConfigParams);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    if ((STW_SOK == status) && (0U != regionParams->regionId))
    {
        /* Remove permission for add masters */
        L3FWRemoveAllRegionMRMPermissions(baseAddr, regionParams->regionId);
        /* Configure region MRM permissions */
        status = FWLIBL3UpdateMRMPermissions(baseAddr,
                                             regionParams->regionId,
                                             numOfMasters,
                                             masterList);
    }
    return status;
}

int32_t FWLIBL3UpdateMRMPermissions(uint32_t                baseAddr,
                                    uint32_t                regionId,
                                    uint32_t                numOfMasters,
                                    const l3fwMasterList_t *masterList)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex, loopCnt;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    /* Configure region MRM permissions */
    if (STW_SOK == status)
    {
        if ((gL3FWInst[instIndex].fwNumRegions > regionId))
        {
            for (loopCnt = 0U; loopCnt < numOfMasters; loopCnt++)
            {
                L3FWSetRegionMRMPermission(
                    baseAddr,
                    regionId,
                    masterList[loopCnt].connId,
                    masterList[loopCnt].permission);
            }
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL3RegionEnable(uint32_t baseAddr,
                            uint32_t regionId,
                            uint32_t portNum)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        /* Enable region */
        if ((gL3FWInst[instIndex].fwNumPorts > portNum) &&
            (gL3FWInst[instIndex].fwNumRegions > regionId))
        {
            L3FWEnableRegion(baseAddr,
                             regionId,
                             portNum);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL3RegionDisable(uint32_t baseAddr,
                             uint32_t regionId,
                             uint32_t portNum)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        /* Disable region */
        if ((gL3FWInst[instIndex].fwNumPorts > portNum) &&
            (gL3FWInst[instIndex].fwNumRegions > regionId))
        {
            L3FWDisableRegion(baseAddr,
                              regionId,
                              portNum);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL3GetErrorLog(uint32_t                 baseAddr,
                           uint32_t                 portNum,
                           l3fwRegionErrorStatus_t *errorInfo)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;
    uint32_t regVal;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EBADARGS;
    }
    if (STW_SOK == status)
    {
        /* Return EFAIL if no error in Control Module */
        regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                             gL3FWInst[instIndex].ctrlCoreRegAddr);
        regVal = regVal & gL3FWInst[instIndex].ctrlCoreRegBitField;
        if (regVal == 0U)
        {
            status = STW_EFAIL;
        }
    }
    if (STW_SOK == status)
    {
        if ((gL3FWInst[instIndex].fwNumPorts > portNum))
        {
            /* Get Error Information */
            L3FWGetErrorInfo(baseAddr, portNum, errorInfo);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL3ClearErrorLog(uint32_t baseAddr, uint32_t portNum)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL3GetInstSummary(baseAddr);
    if (L3FW_INST_NUM == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        if ((gL3FWInst[instIndex].fwNumPorts > portNum))
        {
            /* Clear status in Control Module */
            HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                        gL3FWInst[instIndex].ctrlCoreRegAddr,
                        gL3FWInst[instIndex].ctrlCoreRegBitField);
            /* Clear Error Information */
            L3FWClearErrorInfo(baseAddr, portNum);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

uint32_t FWLIBL3GetInstSummary(uint32_t baseAddr)
{
    uint32_t index, loopCnt;

    for (loopCnt = 0U; loopCnt < L3FW_INST_NUM; loopCnt++)
    {
        if (gL3FWInst[loopCnt].fwBaseAddr == baseAddr)
        {
            break;
        }
    }
    index = loopCnt;
    return index;
}
