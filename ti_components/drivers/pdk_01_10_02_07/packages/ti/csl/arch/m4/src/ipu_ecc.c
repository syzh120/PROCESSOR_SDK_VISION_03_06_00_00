/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - www.ti.com/
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
 *  \file   ipu_ecc.c
 *
 *  \brief  This file contains the APIs for configuring IPU_ECC
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdint.h"
#include "string.h"
#include "ti/csl/csl_types.h"
#include "ipu_ecc.h"
#include "ti/csl/hw_types.h"
#include "cslr_cache.h"

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
/*                          Function Declarations                             */
/* ========================================================================== */

/*TI_INSPECTED 65 D : MISRAC_2012_R_2.2
 *"Tool Issue - Unable to process HW_WR MACROS " */
void ECCIPUMemConfig(uint32_t                 baseAddr,
                     const eccIpuMemCfgPrm_t *pCfgPrm)
{
    if (ECC_IPU_MEM_TYPE_L1DATA == pCfgPrm->memType)
    {
        /* To Enable/Disable auto correction when 1 Bit error occurs in IPU
         * L1DATA Memory */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_SEC_AUTO_EN,
                      pCfgPrm->errAutoCorrectEnable);
        /* To Enable/Disable error respose to master when 2 Bit error occurs in
         * IPU L1DATA Memory*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_SRESP_EN,
                      pCfgPrm->sRespHFEnable);
        /*To Enable/Disable IPU L1DATA Memory data mask*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_DATA_MASK,
                      pCfgPrm->dataMask);
        /*To Enable/Disable IPU L1DATA Memory ECC code mask */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_CODE_MASK,
                      pCfgPrm->eccCodeMask);
    }
    else if (ECC_IPU_MEM_TYPE_L1TAG == pCfgPrm->memType)
    {
        /*To Enable/Disable auto correction when 1 Bit error occurs in IPU
         * L1TAG Memory */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_SEC_AUTO_EN,
                      pCfgPrm->errAutoCorrectEnable);
        /*To Enable/Disable error respose to master when 2 Bit error occurs in
         * IPU L1TAG Memory*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_SRESP_EN,
                      pCfgPrm->sRespHFEnable);
        /*To Enable/Disable IPU L1TAG Memory data mask*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_DATA_MASK,
                      pCfgPrm->dataMask);
        /*To Enable/Disable IPU L1TAG Memory ECC code mask */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_CODE_MASK,
                      pCfgPrm->eccCodeMask);
    }
    else if (ECC_IPU_MEM_TYPE_L2RAM == pCfgPrm->memType)
    {
        /* To Enable/Disable auto correction when 1 Bit error occurs in IPU
         * L2RAM Memory */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_SEC_AUTO_EN,
                      pCfgPrm->errAutoCorrectEnable);
        /* To Enable/Disable error respose to master when 2 Bit error occurs in
         * IPU L2RAM Memory*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_SRESP_EN,
                      pCfgPrm->sRespHFEnable);
        /*To Enable/Disable IPU L2RAM Memory data mask*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_DATA_MASK,
                      pCfgPrm->dataMask);
        /*To Enable/Disable IPU L2RAM Memory ECC code mask */
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_CODE_MASK,
                      pCfgPrm->eccCodeMask);
    }
    else
    {
        /* Do nothing*/
    }
}

/*TI_INSPECTED 65 D : MISRAC_2012_R_2.2
 *"Tool Issue - Unable to process HW_WR MACROS " */
void ECCIPUMemEnableEcc(uint32_t baseAddr,
                        uint32_t eccEnable,
                        uint32_t memType)
{
    if (ECC_IPU_MEM_TYPE_L1DATA == memType)
    {
        /*To Enable/ Disable ECC in IPU L1DATA*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1DATA_EN,
                      eccEnable);
    }
    else if (ECC_IPU_MEM_TYPE_L1TAG == memType)
    {
        /*To Enable/ Disable ECC in IPU L1TAG*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L1TAG_EN,
                      eccEnable);
    }
    else if (ECC_IPU_MEM_TYPE_L2RAM == memType)
    {
        /*To Enable/ Disable ECC in IPU L2RAM*/
        HW_WR_FIELD32((baseAddr + IPU_UNICACHE_ECC),
                      IPU_UNICACHE_ECC_L2RAM_EN,
                      eccEnable);
    }
    else
    {
        /* Do nothing*/
    }
}

uint32_t ECCIPUMemGetErrStatus(uint32_t baseAddr,
                               uint32_t memType)
{
    uint32_t eccErrStatus;

    if (ECC_IPU_MEM_TYPE_L1DATA == memType)
    {
        eccErrStatus = HW_RD_REG32(baseAddr + IPU_UNICACHE_L1DATA_ERR_INFO);
    }
    else if (ECC_IPU_MEM_TYPE_L1TAG == memType)
    {
        eccErrStatus = HW_RD_REG32(baseAddr + IPU_UNICACHE_L1TAG_ERR_INFO);
    }
    else if (ECC_IPU_MEM_TYPE_L2RAM == memType)
    {
        eccErrStatus = HW_RD_REG32(baseAddr + IPU_UNICACHE_L2RAM_ERR_INFO);
    }
    else
    {
        /* Invalid case */
        eccErrStatus = 0U;
    }

    return eccErrStatus;
}

int32_t ECCIPUMemClrErrStatus(uint32_t baseAddr,
                              uint32_t eccErr,
                              uint32_t memType)
{
    int32_t retVal;

    if (ECC_IPU_MEM_TYPE_L1DATA == memType)
    {
        HW_WR_REG32((baseAddr + IPU_UNICACHE_L1DATA_ERR_INFO), eccErr);
        retVal = STW_SOK;
    }
    else if (ECC_IPU_MEM_TYPE_L1TAG == memType)
    {
        HW_WR_REG32((baseAddr + IPU_UNICACHE_L1TAG_ERR_INFO), eccErr);
        retVal = STW_SOK;
    }
    else if (ECC_IPU_MEM_TYPE_L2RAM == memType)
    {
        HW_WR_REG32((baseAddr + IPU_UNICACHE_L2RAM_ERR_INFO), eccErr);
        retVal = STW_SOK;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

int32_t ECCIPUMemGetErrInfo(uint32_t  baseAddr,
                            uint32_t *pErrAddr,
                            uint32_t  memType)
{
    int32_t retVal;

    if (pErrAddr == NULL)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        if (ECC_IPU_MEM_TYPE_L1DATA == memType)
        {
            *pErrAddr = HW_RD_REG32(baseAddr + IPU_UNICACHE_L1DATA_ERR_ADDR_LOC);
            retVal = STW_SOK;
        }
        else if (ECC_IPU_MEM_TYPE_L1TAG == memType)
        {
            *pErrAddr = HW_RD_REG32(baseAddr + IPU_UNICACHE_L1TAG_ERR_ADDR_LOC);
            retVal = STW_SOK;
        }
        else if (ECC_IPU_MEM_TYPE_L2RAM == memType)
        {
            *pErrAddr = HW_RD_REG32(baseAddr + IPU_UNICACHE_L2RAM_ERR_ADDR_LOC);
            retVal = STW_SOK;
        }
        else
        {
            *pErrAddr = 0x0U;
            retVal    = STW_EFAIL;
        }
    }

    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
