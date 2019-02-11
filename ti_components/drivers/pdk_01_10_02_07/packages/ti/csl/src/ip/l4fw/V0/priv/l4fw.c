/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file     l4fw.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of L4FW.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_l4fw.h>

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

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void L4FWSetProtGroupMembers(uint32_t baseAddr, uint32_t groupNum,
                             uint32_t connIdVal)
{
    HW_WR_REG32(baseAddr + L4_AP_PROT_GROUP_MEMBERS_L(groupNum), connIdVal);
}

uint32_t L4FWGetProtGroupMembers(uint32_t baseAddr, uint32_t groupNum)
{
    return (HW_RD_REG32(baseAddr + L4_AP_PROT_GROUP_MEMBERS_L(groupNum)));
}

void L4FWSetProtGroupRoles(uint32_t baseAddr, uint32_t groupNum,
                           uint64_t rolesVal)
{
    HW_WR_REG32(baseAddr + L4_AP_PROT_GROUP_ROLES_L(groupNum),
                (rolesVal & 0x00000000FFFFFFFFU));
    HW_WR_REG32(baseAddr + L4_AP_PROT_GROUP_ROLES_H(groupNum),
                ((rolesVal & 0xFFFFFFFF00000000U)) >> 32U);
}

uint64_t L4FWGetProtGroupRoles(uint32_t baseAddr, uint32_t groupNum)
{
    uint64_t rolesVal = 0;
    uint32_t rolesVal32Bit = 0;
    rolesVal32Bit = HW_RD_REG32(baseAddr + L4_AP_PROT_GROUP_ROLES_L(groupNum));
    rolesVal |= ((uint64_t) rolesVal32Bit);
    rolesVal32Bit = HW_RD_REG32(baseAddr + L4_AP_PROT_GROUP_ROLES_H(groupNum));
    rolesVal |= (((uint64_t) rolesVal32Bit) << 32U);
    return rolesVal;
}

void L4FWSetRegionProtGroupId(uint32_t baseAddr, uint32_t regionNum,
                              uint32_t protGroupId)
{
    HW_WR_FIELD32(baseAddr + L4_AP_REGION_H(
                      regionNum), L4_AP_REGION_H_PROT_GROUP_ID, protGroupId);
}

uint32_t L4FWGetRegionProtGroupId(uint32_t baseAddr, uint32_t regionNum)
{
    return (HW_RD_FIELD32(baseAddr + L4_AP_REGION_H(regionNum),
                          L4_AP_REGION_H_PROT_GROUP_ID));
}

int32_t L4FWGetRegionSizeParams(uint32_t baseAddr, uint32_t regionNum,
                                L4FWRegionSizeParams_t *regionSizeParam)
{
    uint32_t segmentNo;
    regionSizeParam->regionBaseAddr =
        HW_RD_FIELD32(baseAddr + L4_AP_REGION_L(regionNum), L4_AP_REGION_L_BASE);
    regionSizeParam->regionSize =
        HW_RD_FIELD32(baseAddr + L4_AP_REGION_H(regionNum), L4_AP_REGION_H_SIZE);

    segmentNo = HW_RD_FIELD32(baseAddr + L4_AP_REGION_H(
                                  regionNum), L4_AP_REGION_H_SEGMENT_ID);
    regionSizeParam->segmentBaseAddr =
        HW_RD_FIELD32(baseAddr + L4_AP_SEGMENT_L(
                          segmentNo), L4_AP_SEGMENT_L_BASE);
    regionSizeParam->segmentSize =
        HW_RD_FIELD32(baseAddr + L4_AP_SEGMENT_H(
                          segmentNo), L4_AP_SEGMENT_H_SIZE);
    return 0;
}

void L4FWGetErrorLog(uint32_t baseAddr, uint32_t portNum,
                     L4FWErrStat_t *errStat)
{
    uint32_t regVal;
    regVal = HW_RD_REG32(baseAddr + L4_IA_ERROR_LOG_L(portNum));
    errStat->fwErrorCode = HW_GET_FIELD(regVal, L4_IA_AGENT_ERROR_LOG_L_CODE);
    if (errStat->fwErrorCode != L4_IA_AGENT_ERROR_LOG_L_CODE_NO_ERROR)
    {
        errStat->fwErrorConnId = HW_GET_FIELD(regVal,
                                              L4_IA_AGENT_ERROR_LOG_L_CONNID);
        errStat->fwErrorCmd = HW_GET_FIELD(regVal,
                                           L4_IA_AGENT_ERROR_LOG_L_CMD);
        errStat->fwErrorBaseAddr = HW_RD_REG32(baseAddr +
                                               L4_IA_ERROR_LOG_ADDR_L(portNum));
    }
}

int32_t L4FWClrAllErrors(uint32_t baseAddr, uint32_t portNum)
{
    /* Clear error bits in ERROR_LOG_L register */
    uint32_t allErrorMask, regVal;

    /* Clear error bits in STATUS_L register first */
    allErrorMask = L4_IA_AGENT_STATUS_L_INBAND_ERROR_MASK |
                   L4_IA_AGENT_STATUS_L_PROT_ERROR_PRIMARY_MASK |
                   L4_IA_AGENT_STATUS_L_PROT_ERROR_SECONDARY_MASK;
    HW_WR_REG32(baseAddr + L4_IA_AGENT_STATUS_L(portNum), allErrorMask);
    regVal = HW_RD_REG32(baseAddr + L4_IA_ERROR_LOG_L(portNum));
    HW_WR_REG32(baseAddr + L4_IA_ERROR_LOG_L(portNum), regVal);

    return 0;
}

