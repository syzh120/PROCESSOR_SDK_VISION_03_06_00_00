/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file     l3fw.c
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
#include <ti/csl/csl_l3fw.h>

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
 * \brief   This API will block transactions to reach the slave NIU.
 *          This API is called before updating configuration registers.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 *
 * \return  None.
 */
static void L3FWBlockTransactions(uint32_t baseAddr);

/**
 * \brief   This API will allow transactions to reach the slave NIU.
 *          This API is called after updating configuration registers.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 *
 * \return  None.
 */
static void L3FWAllowTransactions(uint32_t baseAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void L3FWSetRegionParams(uint32_t                        baseAddr,
                         const l3fwRegionConfigParams_t *regionParams)
{
    uint32_t startAddr, endAddr, addrShift;

    L3FWBlockTransactions(baseAddr);
    addrShift = HW_RD_FIELD32((baseAddr + L3FW_REGUPDATE_CONTROL),
                              L3FW_REGUPDATE_CONTROL_FW_ADDR_SPACE_MSB);
    /* Calculate start address for target */
    startAddr = (regionParams->regionStartAddr -
                 regionParams->targetBaseAddr);
    startAddr = (startAddr >> addrShift);
    startAddr = (startAddr >> L3FW_START_REGION_START_REGION_1_SHIFT);
    /* Calculate end address for target */
    endAddr = (regionParams->regionEndAddr -
               regionParams->targetBaseAddr);
    endAddr = endAddr - (1U);
    endAddr = (endAddr >> addrShift);
    endAddr = (endAddr >> L3FW_END_REGION_END_REGION_1_SHIFT);

    /* Ignoring Region 0 as Start and End address params are not valid */
    if (0U != regionParams->regionId)
    {
        /* Set start region */
        HW_WR_FIELD32(baseAddr + L3FW_START_REGION(regionParams->regionId),
                      L3FW_START_REGION_START_REGION_1,
                      startAddr);
        /* Set end region */
        HW_WR_FIELD32(baseAddr + L3FW_END_REGION(regionParams->regionId),
                      L3FW_END_REGION_END_REGION_1,
                      endAddr);
    }
    /* Set region permission Address - allowed even for region 0 */
    HW_WR_REG32(baseAddr +
                L3FW_MRM_PERMISSION_REGION_LOW(regionParams->regionId),
                regionParams->regionPermission);
    L3FWAllowTransactions(baseAddr);
}

void L3FWGetRegionParams(uint32_t                  baseAddr,
                         l3fwRegionConfigParams_t *regionParams)
{
    uint32_t addrShift, startAddr, endAddr;

    addrShift = HW_RD_FIELD32(baseAddr + L3FW_REGUPDATE_CONTROL,
                              L3FW_REGUPDATE_CONTROL_FW_ADDR_SPACE_MSB);
    /* Calculate start address */
    startAddr = HW_RD_FIELD32(baseAddr +
                              L3FW_START_REGION(regionParams->regionId),
                              L3FW_START_REGION_START_REGION_1);
    startAddr = startAddr << L3FW_START_REGION_START_REGION_1_SHIFT;
    startAddr = startAddr << addrShift;
    startAddr = startAddr + regionParams->targetBaseAddr;
    /* Calculate end address */
    endAddr = HW_RD_FIELD32(baseAddr +
                            L3FW_END_REGION(regionParams->regionId),
                            L3FW_END_REGION_END_REGION_1);
    endAddr = endAddr << L3FW_END_REGION_END_REGION_1_SHIFT;
    endAddr = endAddr << addrShift;
    endAddr = endAddr + (L3FW_ADDRESS_ALIGNMENT);
    endAddr = endAddr + regionParams->targetBaseAddr;

    regionParams->regionPermission = HW_RD_REG32(baseAddr +
                                                 L3FW_MRM_PERMISSION_REGION_LOW(
                                                     regionParams->regionId));
    regionParams->regionStartAddr = startAddr;
    regionParams->regionEndAddr   = endAddr;
}

void L3FWEnableRegion(uint32_t baseAddr,
                      uint32_t regionId,
                      uint32_t portNum)
{
    uint32_t regVal = 0x0U;

    /* Ignoring Region 0 as it is always enabled */
    if (0U != regionId)
    {
        L3FWBlockTransactions(baseAddr);
        regVal |= HW_RD_REG32(baseAddr +
                              L3FW_END_REGION(regionId));
        regVal |= ((uint32_t) 0x1U << portNum);
        HW_WR_REG32(baseAddr + L3FW_END_REGION(regionId), regVal);
        L3FWAllowTransactions(baseAddr);
    }
}

void L3FWDisableRegion(uint32_t baseAddr,
                       uint32_t regionId,
                       uint32_t portNum)
{
    uint32_t regVal = 0x0U;

    /* Ignoring Region 0 as it is always enabled */
    if (0U != regionId)
    {
        L3FWBlockTransactions(baseAddr);
        regVal |= ~((uint32_t) 0x1U << portNum);
        regVal &= HW_RD_REG32(baseAddr +
                              L3FW_END_REGION(regionId));
        HW_WR_REG32(baseAddr + L3FW_END_REGION(regionId), regVal);
        L3FWAllowTransactions(baseAddr);
    }
}

void L3FWSetRegionMRMPermission(uint32_t baseAddr,
                                uint32_t regionId,
                                uint32_t connId,
                                uint32_t accessType)
{
    uint32_t regVal, addrShift;

    /* L3 uses upper 4 bits of connId */
    connId    = connId >> 2U;
    connId   &= 0xFU;
    addrShift = connId * 2U;
    L3FWBlockTransactions(baseAddr);
    regVal = HW_RD_REG32(baseAddr +
                         L3FW_MRM_PERMISSION_REGION_HIGH(regionId));
    regVal &= (~((uint32_t) L3FW_MRM_RW_PERMISSION_READ_WRITE <<
                 addrShift));
    regVal |= (accessType << addrShift);
    HW_WR_REG32(baseAddr + L3FW_MRM_PERMISSION_REGION_HIGH(regionId), regVal);
    L3FWAllowTransactions(baseAddr);
}

void L3FWGetRegionMRMPermission(uint32_t  baseAddr,
                                uint32_t  regionId,
                                uint32_t  connId,
                                uint32_t *pAccessType)
{
    uint32_t regVal, addrShift;
    *pAccessType = 0U;

    /* L3 uses upper 4 bits of connId */
    connId    = connId >> 2U;
    connId   &= 0xFU;
    addrShift = connId * 2U;
    regVal    = HW_RD_REG32(baseAddr +
                            L3FW_MRM_PERMISSION_REGION_HIGH(regionId));
    regVal       = (regVal >> addrShift);
    *pAccessType = (regVal & L3FW_MRM_RW_PERMISSION_READ_WRITE);
}

void L3FWRemoveAllRegionMRMPermissions(uint32_t baseAddr,
                                       uint32_t regionId)
{
    L3FWBlockTransactions(baseAddr);
    HW_WR_REG32(baseAddr + L3FW_MRM_PERMISSION_REGION_HIGH(regionId),
                0x00000000U);
    L3FWAllowTransactions(baseAddr);
}

void L3FWAddAllRegionMRMPermissions(uint32_t baseAddr,
                                    uint32_t regionId)
{
    L3FWBlockTransactions(baseAddr);
    HW_WR_REG32(baseAddr + L3FW_MRM_PERMISSION_REGION_HIGH(regionId),
                0xFFFFFFFFU);
    L3FWAllowTransactions(baseAddr);
}

void L3FWResetAllRegions(uint32_t baseAddr)
{
    HW_WR_REG32(baseAddr + L3FW_REGUPDATE_CONTROL, 0x2U);
}

void L3FWGetErrorInfo(uint32_t                 baseAddr,
                      uint32_t                 portNum,
                      l3fwRegionErrorStatus_t *errorInfo)
{
    uint32_t regVal;
    uint32_t addrShift;

    addrShift =
        HW_RD_FIELD32(baseAddr + L3FW_REGUPDATE_CONTROL,
                      L3FW_REGUPDATE_CONTROL_FW_ADDR_SPACE_MSB);

    regVal =
        HW_RD_FIELD32(baseAddr + L3FW_ERROR_LOG(portNum),
                      L3FW_ERROR_LOG_REQINFO_ERRLOG);
    errorInfo->errorStartRegion =
        HW_RD_FIELD32(baseAddr + L3FW_ERROR_LOG(portNum),
                      L3FW_ERROR_LOG_REGION_START_ERRLOG);
    errorInfo->errorEndRegion =
        HW_RD_FIELD32(baseAddr + L3FW_ERROR_LOG(portNum),
                      L3FW_ERROR_LOG_REGION_END_ERRLOG);
    errorInfo->blockBurstViolation =
        HW_RD_FIELD32(baseAddr + L3FW_ERROR_LOG(portNum),
                      L3FW_ERROR_LOG_BLK_BURST_VIOLATION);

    errorInfo->addrOffset =
        HW_RD_FIELD32(baseAddr + L3FW_LOGICAL_ADDR_ERRLOG(portNum),
                      L3FW_LOGICAL_ADDR_ERRLOG_SLVOFS_LOGICAL);
    errorInfo->addrOffset = (errorInfo->addrOffset << addrShift);

    errorInfo->mReqType =
        (regVal & L3FW_ERROR_LOG_MREQTYPE_MASK) >>
        L3FW_ERROR_LOG_MREQTYPE_SHIFT;
    errorInfo->mReqSupervisor =
        (regVal & L3FW_ERROR_LOG_SUPERVISOR_MASK) >>
        L3FW_ERROR_LOG_SUPERVISOR_SHIFT;
    errorInfo->mReqDebug =
        (regVal & L3FW_ERROR_LOG_MREQDEBUG_MASK) >>
        L3FW_ERROR_LOG_MREQDEBUG_SHIFT;
    errorInfo->accessType =
        (regVal & L3FW_ERROR_LOG_MCMD_MASK) >>
        L3FW_ERROR_LOG_MCMD_SHIFT;
    errorInfo->connIdMSB4bit =
        (regVal & L3FW_ERROR_LOG_CONNID_MASK) >>
        L3FW_ERROR_LOG_CONNID_SHIFT;
}

void L3FWClearErrorInfo(uint32_t baseAddr, uint32_t portNum)
{
    HW_WR_REG32(baseAddr + L3FW_ERROR_LOG(portNum), 0x0U);
}

static void L3FWBlockTransactions(uint32_t baseAddr)
{
    HW_WR_REG32(baseAddr + L3FW_REGUPDATE_CONTROL, 0x1U);
}

static void L3FWAllowTransactions(uint32_t baseAddr)
{
    HW_WR_REG32(baseAddr + L3FW_REGUPDATE_CONTROL, 0x0U);
}

