/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \ingroup CSL_ARCH_M4
 *  \defgroup CSL_ARCH_M4_ECC ECC
 *
 *  @{
 */
/**
 *  \file  ipu_ecc.h
 *
 *  \brief This file contains the API prototypes for configuring ECC for
 *         ARM Cortex-M4
 *
 */

#ifndef IPU_ECC_H_
#define IPU_ECC_H_

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

/** \brief Macros that can be used to clear different types of Errors in IPU
 *         L2RAM / L1Data / L1Tag Error Info
 */
/*
 * \name Macros that can be used to clear different types of Errors in IPU
 *       L2RAM / L1Data / L1Tag Error Info
 * @{
 */
/**
 * \brief IPU L2RAM / L1Data / L1Tag Memory 1 bit ECC Error
 */
#define ECC_IPU_ERR_ONEBIT    (0x1U)
/**
 * \brief IPU L2RAM / L1Data / L1Tag Memory 2 bit ECC Error
 */
#define ECC_IPU_ERR_TWOBIT    (0x4U)
/**
 * \brief IPU L2RAM / L1Data / L1Tag Memory ECC Error in Code Area
 */
#define ECC_IPU_ERR_CODE      (0x2U)
/**
 * \brief IPU L2RAM / L1Data / L1Tag Memory
 *        All ECC Error : 1bit, 2bit and code ecc error
 */
#define ECC_IPU_ERR_ALL       (ECC_IPU_ERR_ONEBIT | \
                               ECC_IPU_ERR_TWOBIT | \
                               ECC_IPU_ERR_CODE)
/* @} */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief    Enumerates the values used to represent IPU ECC Memory types
 */
typedef enum eccIpuMemType
{
    ECC_IPU_MEM_TYPE_L2RAM = 0x1U,
    /**<  IPU L2RAM ECC Memory Type */
    ECC_IPU_MEM_TYPE_L1DATA = 0x2U,
    /**<  IPU L1DATA ECC Memory Type */
    ECC_IPU_MEM_TYPE_L1TAG = 0x4U
    /**<  IPU L1TAG ECC Memory Type */
} eccIpuMemType_t;

/**
 * \brief Structure holding ECC configuration parameters of
 *        IPU L2RAM /L1Data / L1TAG Memory
 */
typedef struct eccIpuMemCfgPrm
{
    uint32_t errAutoCorrectEnable;
    /**<  To Enable/Disable auto correction when 1 Bit error occurs in
     *    IPU L2RAM /L1DATA / L1TAG Memory. Valid values: TRUE or FALSE */
    uint32_t sRespHFEnable;
    /**<  To Enable/Disable error signal response (Hard Fault) to master i.e.
     *    IPU in case of Double Error Detection in IPU L2RAM /L1DATA/L1TAG
     *    Memory. Valid values: TRUE or FALSE */
    uint32_t dataMask;
    /**<  To Enable/Disable data Mask in IPU L2RAM /L1DATA / L1TAG Memory
     *     Valid values: TRUE or FALSE */
    uint32_t eccCodeMask;
    /**<  To Enable/Disable ECC code Mask in IPU L2RAM / L1DATA / L1TAG Memory
     *    Valid values: TRUE or FALSE */
    uint32_t memType;
    /**<  ECC IPU Memory Type. For valid values refer enum #eccIpuMemType_t */
} eccIpuMemCfgPrm_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function configures ECC configuration parameters for
 *          IPU L2RAM /L1Data / L1TAG Memory
 *
 * \param   baseAddr          Base address for IPU_UNICACHE_CFG register
 * \param   pCfgPrm           Pointer which holds ECC configuration parameters
 *                            for IPU L2RAM /L1Data / L1TAG Memory. Refer
 *                            #eccIpuMemCfgPrm_t for details on the structure.
 *
 * \return  None
 */
void ECCIPUMemConfig(uint32_t                 baseAddr,
                     const eccIpuMemCfgPrm_t *pCfgPrm);

/**
 * \brief   This function will enable/disable ECC in IPU L2RAM / L1DATA / L1TAG
 *          Memory for the defined ECC IPU Memory type
 *
 * \param   baseAddr            Base address for IPU_UNICACHE_CFG register
 * \param   eccEnable           To Enable/Disable ECC in IPU L2RAM / L1DATA /
 *                              L1TAG Memory
 *                              Valid values: TRUE or FALSE
 * \param   memType             ECC IPU Memory Type
 *                              For valid values refer enum #eccIpuMemType_t
 *
 * \return  None
 */
void ECCIPUMemEnableEcc(uint32_t baseAddr,
                        uint32_t eccEnable,
                        uint32_t memType);

/**
 * \brief   This function will return IPU L2RAM / L1DATA / L1TAG Memory
 *          Error status when 1 Bit or 2 Bit Error occurs for the defined
 *          ECC IPU Memory type
 *
 * \param   baseAddr         Base address for IPU_UNICACHE_CFG register
 * \param   memType          ECC IPU Memory Type
 *                           For valid values refer enum #eccIpuMemType_t
 *
 * \return  Returns the IPU L2RAM / L1DATA / L1TAG Memory Error status when
 *          1 Bit or 2 Bit Error occurs
 */
uint32_t ECCIPUMemGetErrStatus(uint32_t baseAddr,
                               uint32_t memType);

/**
 * \brief   This function will clear error status of the defined
 *          ECC Error for the defined ECC IPU Memory type
 *
 * \param   baseAddr         Base address for IPU_UNICACHE_CFG register
 * \param   eccErr           Ecc Error which needs to be cleared
 * \param   memType          ECC IPU Memory Type
 *                           For valid values refer enum #eccIpuMemType_t
 *
 * \return  status           STW_SOK: When the API clears the error successfully
 *                           STW_EFAIL: When the API fails to clear error
 */
int32_t ECCIPUMemClrErrStatus(uint32_t baseAddr,
                              uint32_t eccErr,
                              uint32_t memType);

/**
 * \brief   This function will return the IPU L2RAM / L1DATA / L1TAG Memory
 *          error information when 1 Bit or 2 Bit Error occurs for the defined
 *          ECC IPU Memory type
 *
 * \param   baseAddr       Base address for IPU_UNICACHE_CFG register
 * \param   pErrAddr       Pointer which hold Error Address when 1 Bit or
 *                         2 Bit Error occurs
 * \param   memType        ECC IPU Memory Type
 *                         For valid values refer enum #eccIpuMemType_t
 *
 * \return  STW_SOK on success else STW_EFAIL
 */
int32_t ECCIPUMemGetErrInfo(uint32_t  baseAddr,
                            uint32_t *pErrAddr,
                            uint32_t  memType);

#ifdef __cplusplus
}
#endif
#endif
 /** @} */
