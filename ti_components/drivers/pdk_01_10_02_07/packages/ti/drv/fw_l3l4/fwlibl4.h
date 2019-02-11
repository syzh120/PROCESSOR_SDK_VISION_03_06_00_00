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
 *  \defgroup FIREWALL_L4_DRIVER L4 Firewall Driver API
 *
 *  @{
 */
/**
 *  \file     fwlibl4.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of L4FW.
 *            This also contains some related macros.
 *
 *  \copyright Copyright (C) 2016 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

#ifndef FWLIBL4_H_
#define FWLIBL4_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_l4fw.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief   Maximum number of Port groups for L4 Firewall
 */
#define L4FW_MAX_PROT_GROUPS                                (8U)
/**
 * \brief   Maximum number of Port for L4 Firewall
 */
#define L4FW_MAX_PORTS                                      (3U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Structure for L4 Firewall Instance summary.
 */
typedef struct l4fwInstSummary
{
    uint32_t fwBaseAddr;
    /**< L3 Firewall Instance Base Address */
    uint32_t fwNumProtGroup;
    /**< Number of protection groups in in L4 Firewall */
    uint32_t fwNumRegions;
    /**< Number of regions for L3 Firewall Instance */
    uint32_t fwNumPorts;
    /**< Number of ports in Target */
    uint32_t ctrlCoreRegAddr;
    /**< Address of corresponding CTRL_CORE_SEC_ERR_STATUS_FUNC_x register */
    uint32_t ctrlCoreRegBitField;
    /**< Bit-field of corresponding CTRL_CORE_SEC_ERR_STATUS_FUNC_x register */
}l4fwInstSummary_t;

/**
 * \brief  Structure for All L4 Firewall Instance Error status.
 */
typedef struct l4fwAllApErrors
{
    L4FWErrStat_t l4Err[L4FW_NUM_INST][L4FW_MAX_PORTS];
    /**< Array Error Status structure per IA port for each L4FW Instance. */
}l4fwAllApErrors_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief This function sets protection group for a region
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   regionNum   region Number of the Firewall
 *
 * @param   groupNum    Protection group Number to be assigned
 *
 * @return  STW_SOK on success
 */
int32_t FWLIBL4SetRegionProtGroupId(uint32_t baseAddr,
                                    uint32_t regionNum,
                                    uint32_t groupNum);

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
 * @return  STW_SOK on success
 */
int32_t FWLIBL4SetProtGroupMembers(uint32_t baseAddr,
                                   uint32_t groupNum,
                                   uint32_t connIdVal);

/**
 * \brief This function clears and gets L4FW Error status for all instances
 *
 * @param   l4fwAllErr  pointer to structure to write the error status value.
 *
 * @return  STW_SOK on success
 */
int32_t FWLIBL4ClearAndGetAllError(l4fwAllApErrors_t *l4fwAllErr);

/**
 * \brief This function gets instance summary for a L4FW instance
 *
 * @param   baseAddr    Base address of L4 Firewall instance.
 *
 * @param   instSum     Pointer to structure to fill the instance summary.
 *
 * @return  STW_SOK on success
 */
int32_t FWLIBL4GetInstSummary(uint32_t baseAddr, l4fwInstSummary_t *instSum);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
/* @} */
