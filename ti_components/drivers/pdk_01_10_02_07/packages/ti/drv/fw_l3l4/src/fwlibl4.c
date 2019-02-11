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
 *  \file     fwlibl4.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of L4FW.
 *            This also contains some related macros.
 *
 *  \copyright Copyright (C) 2016 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <fwlibl4.h>

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
 *          struct #gL4FWInst.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 *
 * \return  index           Index in gL4FWInst structure.
 */
static uint32_t FWLIBL4GetInstIndex(uint32_t baseAddr);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static l4fwInstSummary_t gL4FWInst[L4FW_NUM_INST] = L4FW_INST_SUMMARY;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t FWLIBL4SetRegionProtGroupId(uint32_t baseAddr,
                                    uint32_t regionNum,
                                    uint32_t groupNum)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL4GetInstIndex(baseAddr);
    if (L4FW_NUM_INST == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        if ((gL4FWInst[instIndex].fwNumRegions > regionNum) &&
            (gL4FWInst[instIndex].fwNumProtGroup > groupNum))
        {
            L4FWSetRegionProtGroupId(baseAddr, regionNum, groupNum);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL4SetProtGroupMembers(uint32_t baseAddr,
                                   uint32_t groupNum,
                                   uint32_t connIdVal)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    /* Get L3 Firewall instance details */
    instIndex = FWLIBL4GetInstIndex(baseAddr);
    if (L4FW_NUM_INST == instIndex)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        if (gL4FWInst[instIndex].fwNumProtGroup > groupNum)
        {
            L4FWSetProtGroupMembers(baseAddr, groupNum, connIdVal);
        }
        else
        {
            status = STW_EFAIL;
        }
    }
    return status;
}

int32_t FWLIBL4GetInstSummary(uint32_t baseAddr, l4fwInstSummary_t *instSum)
{
    int32_t  status = STW_SOK;
    uint32_t instIndex;

    if (instSum == NULL)
    {
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        /* Get L3 Firewall instance details */
        instIndex = FWLIBL4GetInstIndex(baseAddr);
        if (L4FW_NUM_INST == instIndex)
        {
            status = STW_EFAIL;
        }
    }
    if (STW_SOK == status)
    {
        instSum->fwBaseAddr     = gL4FWInst[instIndex].fwBaseAddr;
        instSum->fwNumProtGroup = gL4FWInst[instIndex].fwNumProtGroup;
        instSum->fwNumRegions   = gL4FWInst[instIndex].fwNumRegions;
        instSum->fwNumPorts     = gL4FWInst[instIndex].fwNumPorts;
    }
    return status;
}

static uint32_t FWLIBL4GetInstIndex(uint32_t baseAddr)
{
    uint32_t idx, loopCnt;

    for (loopCnt = 0U; loopCnt < L4FW_NUM_INST; loopCnt++)
    {
        if (gL4FWInst[loopCnt].fwBaseAddr == baseAddr)
        {
            break;
        }
    }
    idx = loopCnt;
    return idx;
}

int32_t FWLIBL4ClearAndGetAllError(l4fwAllApErrors_t *l4fwAllErr)
{
    int32_t  retVal = STW_SOK;
    uint32_t regVal;
    uint32_t loopCnt, portCnt;
    uint32_t errCnt = 0U;

    if (l4fwAllErr == NULL)
    {
        retVal = STW_EFAIL;
    }

    if (retVal == STW_SOK)
    {
        for (loopCnt = 0U; loopCnt < L4FW_NUM_INST; loopCnt++)
        {
            regVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                                 gL4FWInst[loopCnt].ctrlCoreRegAddr);
            if ((regVal & gL4FWInst[loopCnt].ctrlCoreRegBitField) != 0)
            {
                /* Clear Control module error status */
                HW_WR_REG32(
                    (SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                     gL4FWInst[loopCnt].ctrlCoreRegAddr),
                    gL4FWInst[loopCnt].ctrlCoreRegBitField);
                for (portCnt = 0; portCnt < gL4FWInst[loopCnt].fwNumPorts;
                     portCnt++)
                {
                    l4fwAllErr->l4Err[errCnt][portCnt].fwBaseAddr =
                        gL4FWInst[loopCnt].fwBaseAddr;

                    L4FWGetErrorLog(gL4FWInst[loopCnt].fwBaseAddr,
                                    portCnt,
                                    &(l4fwAllErr->l4Err[errCnt][portCnt]));
                    #if (defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_AM572x) || defined (SOC_TDA2EX) || defined (SOC_AM571x))
                    /* In case of Tda2xx and Tda2ex L4per3 connId is left
                     * shifted by 1 bit. Errata i871.
                     */
                    if(SOC_L4_PER3_AP_BASE == gL4FWInst[loopCnt].fwBaseAddr)
                    {
                        /* right shift the connId value by 1 bit */
                        uint32_t connIdVal;
                        connIdVal =
                            l4fwAllErr->l4Err[errCnt][portCnt].fwErrorConnId;
                        connIdVal = connIdVal >> 1U;
                        l4fwAllErr->l4Err[errCnt][portCnt].fwErrorConnId =
                            connIdVal;
                    }
                    #endif
                    L4FWClrAllErrors(gL4FWInst[loopCnt].fwBaseAddr, portCnt);
                }
                errCnt++;
            }
        }
    }
    return retVal;
}

