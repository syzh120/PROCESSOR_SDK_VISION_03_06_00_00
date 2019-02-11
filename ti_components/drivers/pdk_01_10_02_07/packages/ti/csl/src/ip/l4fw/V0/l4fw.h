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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_L4_FIREWALL L4 Firewall
 *
 *  @{
 */
/**
 *  \file     l4fw.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of L4FW.
 *            This also contains some related macros.
 */

#ifndef L4FW_H_
#define L4FW_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_l4fw.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Structure size parameters for L4 FW region.
 */
typedef struct L4FWRegionSizeParams
{
    uint32_t regionBaseAddr;
    /**< L4 Firewall Region Base Address */
    uint32_t regionSize;
    /**< Size of the region. The size will be (2 ** regionSize). */
    uint32_t segmentBaseAddr;
    /**< L4 Firewall segment Base Address corresponding to region*/
    uint32_t segmentSize;
    /**< Size of the segment. The size will be (2 ** segmentSize). */
}L4FWRegionSizeParams_t;

/**
 * \brief  Structure Error status for L4 FW per IA port.
 */
typedef struct l4fwErrStat
{
    uint32_t fwBaseAddr;
    /**< L4 Firewall Instance Base Address */
    uint32_t fwErrorCode;
    /**< Error Code */
    uint32_t fwErrorCmd;
    /**< Command type which caused L4 Firewall error */
    uint32_t fwErrorConnId;
    /**< Conn Id of the initiator which caused L4 Firewall error */
    uint32_t fwErrorBaseAddr;
    /**< Offset base address which caused the L4 Firewall error */
}L4FWErrStat_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief This function sets connId values for a protection group
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   groupNum    Protection group Number
 *
 * @param   connIdVal   Bitfields corresponding to connId values to enable the
 *                      firewall access for the group
 *
 * @return  None
 */
void L4FWSetProtGroupMembers(uint32_t baseAddr, uint32_t groupNum,
                             uint32_t connIdVal);
/**
 * \brief This function gets connId values for a protection group
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   groupNum    Protection group Number
 *
 * @return  Bitfields corresponding to connId values that have the firewall
 *          firewall access for the group
 *
 */
uint32_t L4FWGetProtGroupMembers(uint32_t baseAddr, uint32_t groupNum);

/**
 * \brief This function sets roles for a protection group
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   groupNum    Protection group Number
 *
 * @param  rolesVal    roles value to set the for the group
 *
 * @return  None
 */
void L4FWSetProtGroupRoles(uint32_t baseAddr, uint32_t groupNum,
                           uint64_t rolesVal);

/**
 * \brief This function gets roles for a protection group
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   groupNum    Protection group Number
 *
 * @return  roles value of the group
 *
 */
uint64_t L4FWGetProtGroupRoles(uint32_t baseAddr, uint32_t groupNum);

/**
 * \brief This function sets protection group for a region
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   regionNum   region Number of the Firewall
 *
 * @param   protGroupId Protection group Number to be assigned
 *
 * @return  None
 */
void L4FWSetRegionProtGroupId(uint32_t baseAddr, uint32_t regionNum,
                              uint32_t protGroupId);

/**
 * \brief This function gets protection group associated with a region
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   regionNum   region Number of the Firewall
 *
 * @return  protection group associated with region
 *
 */
uint32_t L4FWGetRegionProtGroupId(uint32_t baseAddr, uint32_t regionNum);

/**
 * \brief This function gets size parameters of a region
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   regionNum   region Number of the Firewall
 *
 * @param   regionSizeParam     This is a pointer to structure to fill the size
 *                              parameters corresponding to the region
 *
 * @return  STW_SOK on success
 */
int32_t L4FWGetRegionSizeParams(uint32_t baseAddr, uint32_t regionNum,
                                L4FWRegionSizeParams_t *regionSizeParam);

/**
 * \brief This function gets Error information for an IA port
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   portNum     Initiator port number of the Firewall
 *
 * @param   errStat     This is a pointer to structure to fill the error
 *                      status corresponding to the IA port
 *
 * @return  none
 */
void L4FWGetErrorLog(uint32_t baseAddr, uint32_t portNum,
                     L4FWErrStat_t *errStat);

/**
 * \brief This function Clears Error status for an IA port
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   portNum     Initiator port number of the Firewall
 *
 * @return  STW_SOK on success
 */
int32_t L4FWClrAllErrors(uint32_t baseAddr, uint32_t portNum);
#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
 /** @} */
