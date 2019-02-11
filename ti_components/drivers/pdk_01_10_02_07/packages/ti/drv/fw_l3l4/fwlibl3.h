/*
 *  Copyright (C) 2015 Texas Instruments Incorporated
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
 *  \defgroup FIREWALL_L3_DRIVER L3 Firewall Driver API
 *
 *  @{
 */
/**
 *  \file     fwlibl3.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of L3FW.
 *            This also contains some related macros.
 */

#ifndef FWLIBL3_H_
#define FWLIBL3_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_l3fw.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief   Maximum number of masters for L3 Firewall
 */
#define L3FW_NUM_MASTER_MAX                                 (16U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Structure for L3 Firewall Instance summary.
 */
typedef struct l3fwInstSummary
{
    uint32_t fwBaseAddr;
    /**< L3 Firewall Instance Base Address */
    uint32_t fwNumRegions;
    /**< Number of regions for L3 Firewall Instance */
    uint32_t fwNumPorts;
    /**< Number of ports in Target */
    uint32_t ctrlCoreRegAddr;
    /**< Address of corresponding CTRL_CORE_SEC_ERR_STATUS_FUNC_x register */
    uint32_t ctrlCoreRegBitField;
    /**< Bit-field of corresponding CTRL_CORE_SEC_ERR_STATUS_FUNC_x register */
}l3fwInstSummary_t;

/**
 * \brief  Structure for L3 Firewall Masters list along with with permission.
 */
typedef struct l3fwMasterList
{
    uint32_t connId;
    /**< ConnId of type halL3fwL3ConnId which made the invalid access
     *  This ID should be 4bit connID
     *  (upper 4 bits of 6bit connID).
     */
    uint32_t permission;
    /**< Number of regions for L3 Firewall Instance
     *  Refer enum l3fwMRMRWPermission_t
     */
}l3fwMasterList_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
#if defined (SOC_TDA2PX)
#if defined (__ARM_ARCH_7A__)
/**
 * \brief   This API will read and return mreqDoamin ID for given initiator.
 *
 * \param   initiator       Initiator ID.
 *                          Refer to enum #CSL_mreqDomainInitiator_t
 *
 * \return  mreqDomain ID.
 * NOTE:    This function can be only called from A15.
 */
uint32_t FWLIBL3MReqDomainReadDomainId(uint32_t initiator);

/**
 * \brief   This API will configure mreqDoamin ID for given initiator.
 *
 * \param   initiator       Initiator ID.
 *                          Refer to enum #CSL_mreqDomainInitiator_t
 * \param   domainId        Desired domain ID.
 *                          Refer enum #CSL_mreqDomainId_t.
 * NOTE:    This function can be only called from A15. Also this function calls
 *          a function which in tern calls ROM API to configure the domain ID.
 *
 * \return  configuration status.
 */
int32_t FWLIBL3MReqDomainWriteDomainId(uint32_t initiator, uint32_t domainId);
#endif
#endif

/**
 * \brief   This API will configure region for L3FW Module.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionParams    Configuration parameters for region.
 * \param   numOfMasters    Number of masters for which MRM permission
 *                          is to set.
 * \param   masterList      List containing list of masters along with
 *                          permissions.
 *
 * \return  status          Configuration status.
 */
int32_t FWLIBL3ConfigRegion(uint32_t                        baseAddr,
                            const l3fwRegionConfigParams_t *regionParams,
                            uint32_t                        numOfMasters,
                            const l3fwMasterList_t         *masterList);

/**
 * \brief   This API will update MRM permissions for a region for L3FW Module.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to configure.
 * \param   numOfMasters    Number of masters for which MRM permission
 *                          is to set.
 * \param   masterList      List containing list of masters along with
 *                          permissions.
 *
 * \return  status          Configuration status.
 */
int32_t FWLIBL3UpdateMRMPermissions(uint32_t                baseAddr,
                                    uint32_t                regionId,
                                    uint32_t                numOfMasters,
                                    const l3fwMasterList_t *masterList);

/**
 * \brief   This API will enable region for port for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to enable.
 * \param   portNum         Port number for which region is to enable.
 *
 * \return  status          Configuration status.
 */
int32_t FWLIBL3RegionEnable(uint32_t baseAddr,
                            uint32_t regionId,
                            uint32_t portNum);

/**
 * \brief   This API will disable region for port for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to disable.
 * \param   portNum         Port number for which region is to disable.
 *
 * \return  status          Configuration status.
 */
int32_t FWLIBL3RegionDisable(uint32_t baseAddr,
                             uint32_t regionId,
                             uint32_t portNum);

/**
 * \brief   This API will read and return error information for L3FW Module
 *          for given port number.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   portNum         Port number.
 * \param   errorInfo       Error information.
 *                          Refer enum l3fwRegionErrorStatus_t.
 *                          Contents valid only if status = STW_SOK
 *
 * \return  status          Returns STW_EBADARGS if invalid base address
 *                          Returns STW_EFAIL if no error in firewall instance
 *                          Returns STW_SOK otherwise
 */
int32_t FWLIBL3GetErrorLog(uint32_t                 baseAddr,
                           uint32_t                 portNum,
                           l3fwRegionErrorStatus_t *errorInfo);

/**
 * \brief   This API will clear error information for L3FW Module for
 *          given port number.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   portNum         Port number.
 *
 * \return  status          Configuration status..
 */
int32_t FWLIBL3ClearErrorLog(uint32_t baseAddr, uint32_t portNum);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
/* @} */
/**
 * \mainpage  Firewall Library
 *
 * \par IMPORTANT NOTE
 *   <b>
 *   The interfaces defined in this package are bound to change.
 *   Release notes/user guide list the additional limitation/restriction
 *   of this module/interfaces.
 *   </b> See also \ref TI_DISCLAIMER.
 *
 *
 * Firewall Library(fwlib) contains higher level APIs written on top L3 Firewall
 * and L4 Firewall CSL-FL.
 *
 * <b>
 * Also refer to top level user guide for detailed features,
 * limitations and usage description.
 * </b>
 *
 * The fwlib APIs can be broadly divided into the following:
 *
 * - <b> L3 Firewall Library(l3fwlib)
 * </b> (See \ref FIREWALL_L3_DRIVER) <br>
 *  l3fwlib provides APIs for L3 Firewall Configuration.
 *
 * - <b> L4 Firewall Library(l4fwlib)
 * </b> (See \ref FIREWALL_L4_DRIVER) <br>
 *  l4fwlib provides APIs for L4 Firewall Configuration.
 *
 */

/**
 *  \page  TI_DISCLAIMER  TI Disclaimer
 *
 *  \htmlinclude ti_disclaim.htm
 */
