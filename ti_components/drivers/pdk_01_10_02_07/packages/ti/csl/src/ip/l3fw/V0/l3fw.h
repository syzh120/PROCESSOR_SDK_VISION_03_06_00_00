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
 *  \ingroup CSL_IP_MODULE
 *  \defgroup CSL_L3_FIREWALL L3 Firewall
 *
 *  @{
 */
/**
 *  \file     l3fw.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of L3FW.
 *            This also contains some related macros.
 */

#ifndef L3FW_H_
#define L3FW_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/cslr_l3fw.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Macros for programming L3_MAIN Firewall Permission-Setting Register.
 *         MRM permission region macros.
 *         Values used for regionPermission in struct #l3fwRegionConfigParams_t.
 *         User can do OR of multiple of the following macros for giving more
 *         than one permissions at a time.
 */
/** \brief  Public User Exe Access Allowed */
#define L3FW_REGION_PERMISSION_PUB_USR_EXE                         (0x00000040U)
/** \brief  Public User Write Access Allowed */
#define L3FW_REGION_PERMISSION_PUB_USR_WRITE                       (0x00000080U)
/** \brief  Public User Read Access Allowed */
#define L3FW_REGION_PERMISSION_PUB_USR_READ                        (0x00000100U)
/** \brief  Public Privilege Exe Access Allowed */
#define L3FW_REGION_PERMISSION_PUB_PRV_EXE                         (0x00000200U)
/** \brief  Public Privilege Write Access Allowed */
#define L3FW_REGION_PERMISSION_PUB_PRV_WRITE                       (0x00000400U)
/** \brief  Public Privilege Read Access Allowed */
#define L3FW_REGION_PERMISSION_PUB_PRV_READ                        (0x00000800U)
/** \brief  Public User Debug Access Allowed */
#define L3FW_REGION_PERMISSION_PUB_USR_DEBUG                       (0x00004000U)
/** \brief  Public Privilege Debug Access Allowed */
#define L3FW_REGION_PERMISSION_PUB_PRV_DEBUG                       (0x00008000U)

/** \brief  Secure User Exe Access Allowed */
#define L3FW_REGION_PERMISSION_SEC_USR_EXE                         (0x00000001U)
/** \brief  Secure User Write Access Allowed */
#define L3FW_REGION_PERMISSION_SEC_USR_WRITE                       (0x00000002U)
/** \brief  Secure User Read Access Allowed */
#define L3FW_REGION_PERMISSION_SEC_USR_READ                        (0x00000004U)
/** \brief  Secure Privilege Exe Access Allowed */
#define L3FW_REGION_PERMISSION_SEC_PRV_EXE                         (0x00000008U)
/** \brief  Secure Privilege Write Access Allowed */
#define L3FW_REGION_PERMISSION_SEC_PRV_WRITE                       (0x00000010U)
/** \brief  Secure Privilege Read Access Allowed */
#define L3FW_REGION_PERMISSION_SEC_PRV_READ                        (0x00000020U)
/** \brief  Secure User Debug Access Allowed */
#define L3FW_REGION_PERMISSION_SEC_USR_DEBUG                       (0x00001000U)
/** \brief  Secure Privilege Debug Access Allowed */
#define L3FW_REGION_PERMISSION_SEC_PRV_DEBUG                       (0x00002000U)

/** \brief  Domain 0 access enable in functional mode Allowed */
#define L3FW_REGION_PERMISSION_DOMAIN0_FUNC                        (0x00010000U)
/** \brief  Domain 0 access enable in debug mode */
#define L3FW_REGION_PERMISSION_DOMAIN0_DBG                         (0x00020000U)
/** \brief  Domain 1 access enable in functional mode Allowed */
#define L3FW_REGION_PERMISSION_DOMAIN1_FUNC                        (0x00040000U)
/** \brief  Domain 1 access enable in debug mode */
#define L3FW_REGION_PERMISSION_DOMAIN1_DBG                         (0x00080000U)
/** \brief  Domain 2 access enable in functional mode Allowed */
#define L3FW_REGION_PERMISSION_DOMAIN2_FUNC                        (0x00100000U)
/** \brief  Domain 2 access enable in debug mode */
#define L3FW_REGION_PERMISSION_DOMAIN2_DBG                         (0x00200000U)
/** \brief  Domain 3 access enable in functional mode Allowed */
#define L3FW_REGION_PERMISSION_DOMAIN3_FUNC                        (0x00400000U)
/** \brief  Domain 3 access enable in debug mode */
#define L3FW_REGION_PERMISSION_DOMAIN3_DBG                         (0x00800000U)
/** \brief  Domain 4 access enable in functional mode Allowed */
#define L3FW_REGION_PERMISSION_DOMAIN4_FUNC                        (0x01000000U)
/** \brief  Domain 4 access enable in debug mode */
#define L3FW_REGION_PERMISSION_DOMAIN4_DBG                         (0x02000000U)
/** \brief  Domain 5 access enable in functional mode Allowed */
#define L3FW_REGION_PERMISSION_DOMAIN5_FUNC                        (0x04000000U)
/** \brief  Domain 5 access enable in debug mode */
#define L3FW_REGION_PERMISSION_DOMAIN5_DBG                         (0x08000000U)
/** \brief  Domain 6 access enable in functional mode Allowed */
#define L3FW_REGION_PERMISSION_DOMAIN6_FUNC                        (0x10000000U)
/** \brief  Domain 6 access enable in debug mode */
#define L3FW_REGION_PERMISSION_DOMAIN6_DBG                         (0x20000000U)
/** \brief  Domain 7 access enable in functional mode Allowed */
#define L3FW_REGION_PERMISSION_DOMAIN7_FUNC                        (0x40000000U)
/** \brief  Domain 7 access enable in debug mode */
#define L3FW_REGION_PERMISSION_DOMAIN7_DBG                         (0x80000000U)

/** \brief   Macro for 4kB address alignment */
#define L3FW_ADDRESS_ALIGNMENT                                     (0x1000U)
/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief  Enum to program L3_MAIN Firewall Read/Write
 *         Permission-Setting Register.
 */
typedef enum l3fwMRMRWPermission
{
    L3FW_MRM_RW_PERMISSION_NONE = 0x0U,
    /**< No Read/Write permission */
    L3FW_MRM_RW_PERMISSION_READ_ONLY = 0x1U,
    /**< Read permission */
    L3FW_MRM_RW_PERMISSION_WRITE_ONLY = 0x2U,
    /**< Write permission */
    L3FW_MRM_RW_PERMISSION_READ_WRITE = (L3FW_MRM_RW_PERMISSION_READ_ONLY |
                                         L3FW_MRM_RW_PERMISSION_WRITE_ONLY)
                                        /**< Read + Write permission */
}l3fwMRMRWPermission_t;

/**
 * \brief  Structure contains configuration parameters for L3 FW region.
 */
typedef struct l3fwRegionConfigParams
{
    uint32_t regionId;
    /**< L3 Firewall Region ID to configure */
    uint32_t targetBaseAddr;
    /**< L3 Firewall Target Module Base Address */
    uint32_t regionStartAddr;
    /**< Start Address (byte address) for the region.
     *  4 kB aligned address.
     *  Ignored when RegionId = 0.
     */
    uint32_t regionEndAddr;
    /**< End Address (byte address) for the region.
     *  4 kB aligned address.
     */
    uint32_t regionPermission;
    /**< Region access permissions.
     *  Refer 'MRM permission region*' macros for more details.
     */
}l3fwRegionConfigParams_t;

/**
 * \brief  Structure contains configuration parameters for L3 FW region.
 */
typedef struct l3fwRegionErrorStatus
{
    uint32_t mReqType;
    /**< Access type
     *  0 => processor data access 1 => processor instruction fetch,
     */
    uint32_t mReqSupervisor;
    /**< Access mode
     *  1 => Privilege or 0 => USER
     */
    uint32_t mReqDebug;
    /**< Functional/Debug mode
     *  0 => Functional 1 => Debug
     */
    uint32_t accessType;
    /**< Transaction type.
     *  0 => READ or 1 => WRITE
     */
    uint32_t connIdMSB4bit;
    /**< ConnId of type halL3fwL3ConnId which made the invalid access
     *  This ID will be 4bit connID
     *  (upper 4 bits of 6bit connID).
     */
    uint32_t errorStartRegion;
    /**< Region ID hit by invalid access */
    uint32_t errorEndRegion;
    /**< Region ID hit by invalid access */
    uint32_t blockBurstViolation;
    /**< 2D burst not allowed or exceeding allowed size */
    uint32_t addrOffset;
    /**< First Address hit by invalid access
     * User needs to multiply by 2 in case of interleaved EMIF configuration
     */
}l3fwRegionErrorStatus_t;
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API will configure region for L3FW Module.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionParams    Configuration parameters for region.
 *                          Refer enum #l3fwRegionConfigParams_t.
 *
 * \return  None.
 */
void L3FWSetRegionParams(uint32_t                        baseAddr,
                         const l3fwRegionConfigParams_t *regionParams);

/**
 * \brief   This API will read and return configured region parameters for
 *          L3FW Module. User should provide L3FW and region ID initialized in
 *          the structure which is passed as an argument.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param  regionParams     Configuration parameters for region.
 *                          Refer enum #l3fwRegionConfigParams_t.
 *                          For Region 0 Start and End Address is returned as 0.
 *
 * \return  None.
 */
void L3FWGetRegionParams(uint32_t                  baseAddr,
                         l3fwRegionConfigParams_t *regionParams);

/**
 * \brief   This API will enable region for port for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to enable.
 * \param   portNum         Port number for which region is to enable.
 *
 * \return  None.
 */
void L3FWEnableRegion(uint32_t baseAddr,
                      uint32_t regionId,
                      uint32_t portNum);

/**
 * \brief   This API will disable region for port for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to disable.
 * \param   portNum         Port number for which region is to disable.
 *
 * \return  None.
 */
void L3FWDisableRegion(uint32_t baseAddr,
                       uint32_t regionId,
                       uint32_t portNum);

/**
 * \brief   This API will enable/disable read/write access to a region for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to enable.
 * \param   connId          Master's connId for which permission is to set.
 * \param   accessType      Read/Write or both permissions for given region.
 *                          Refer enum #l3fwMRMRWPermission_t.
 *
 * \return  None.
 */
void L3FWSetRegionMRMPermission(uint32_t baseAddr,
                                uint32_t regionId,
                                uint32_t connId,
                                uint32_t accessType);

/**
 * \brief   This API will enable/disable read/write access to a region for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to enable.
 * \param   connId          Master's connId for which permission is to set.
 * \param   pAccessType     Pointer to variable which will be updated with
 *                          current permissions.
 *                          Refer enum #l3fwMRMRWPermission_t.
 *
 * \return  None.
 */
void L3FWGetRegionMRMPermission(uint32_t  baseAddr,
                                uint32_t  regionId,
                                uint32_t  connId,
                                uint32_t *pAccessType);

/**
 * \brief   This API will remove read and write access for all masters
 *          to a region for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to enable.
 *
 * \return  None.
 */
void L3FWRemoveAllRegionMRMPermissions(uint32_t baseAddr,
                                       uint32_t regionId);

/**
 * \brief   This API will allow read and write access for all masters
 *          to a region for L3FW.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   regionId        Region ID to enable.
 *
 * \return  None.
 */
void L3FWAddAllRegionMRMPermissions(uint32_t baseAddr,
                                    uint32_t regionId);

/**
 * \brief   This API will reset all configuration for L3FW.
 *          It will enable full access to all masters.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 *
 * \return  None.
 */
void L3FWResetAllRegions(uint32_t baseAddr);

/**
 * \brief   This API will read and return error information for L3FW Module
 *          for given port number.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   portNum         Port number.
 * \param   errorInfo       Error information.
 *                          Refer enum #l3fwRegionErrorStatus_t.
 *
 * \return  None.
 */
void L3FWGetErrorInfo(uint32_t                 baseAddr,
                      uint32_t                 portNum,
                      l3fwRegionErrorStatus_t *errorInfo);

/**
 * \brief   This API will clear error information for L3FW Module for
 *          given port number.
 *
 * \param   baseAddr        Base Address of the L3FW Registers.
 * \param   portNum         Port number.
 *
 * \return  None.
 */
void L3FWClearErrorInfo(uint32_t baseAddr, uint32_t portNum);

#ifdef __cplusplus
}

#endif /*extern "C" */

#endif
 /** @} */
