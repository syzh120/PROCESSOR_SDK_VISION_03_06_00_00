/*
 *  Copyright (C) 2015-2016 Texas Instruments Incorporated
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
 *  \file     emif.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of EMIF.
 *            This also contains some related macros.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_emif.h>

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

int32_t EMIFConfigECCInitECCParams(uint32_t               baseAddr,
                                   const emifEccCfgPrm_t *pCfgPrm)
{
    uint32_t startAddr;
    uint32_t endAddr;
    uint32_t emifMsbStartAddr;
    const emifEccAddrRangeCfgPrm_t  *pAddrRangeCfgPrm;
    int32_t  retVal = STW_SOK;

    if ((pCfgPrm == NULL) || (pCfgPrm->addrRangeCfgPrm == NULL))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        pAddrRangeCfgPrm = pCfgPrm->addrRangeCfgPrm;
        emifMsbStartAddr = (pCfgPrm->emifStartAddr >> 16U);

        startAddr =
            (((pAddrRangeCfgPrm->startAddr &
               0xFFFF0000U) >> 16U) - emifMsbStartAddr);
        endAddr =
            (((pAddrRangeCfgPrm->endAddr &
               0xFFFF0000U) >> 16U) - emifMsbStartAddr);

        /*Config EMIF_ECC_ADDR_RANGE_NUM_2*/
        if (pAddrRangeCfgPrm->addrRangeNum == EMIF_ECC_ADDR_RANGE_NUM_2)
        {
            HW_WR_FIELD32(baseAddr + EMIF_ECC_ADDRESS_RANGE_2,
                          EMIF_ECC_ADDRESS_RANGE_2_REG_ECC_STRT_ADDR_2,
                          startAddr);

            HW_WR_FIELD32(baseAddr + EMIF_ECC_ADDRESS_RANGE_2,
                          EMIF_ECC_ADDRESS_RANGE_2_REG_ECC_END_ADDR_2,
                          endAddr);
            /*Enable/Disable ECC address range 2*/
            HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                          EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_2_EN,
                          pAddrRangeCfgPrm->enableAddrRange);
        }
        else
        {
            /*Config EMIF_ECC_ADDR_RANGE_NUM_1*/
            HW_WR_FIELD32(baseAddr + EMIF_ECC_ADDRESS_RANGE_1,
                          EMIF_ECC_ADDRESS_RANGE_1_REG_ECC_STRT_ADDR_1,
                          startAddr);

            HW_WR_FIELD32(baseAddr + EMIF_ECC_ADDRESS_RANGE_1,
                          EMIF_ECC_ADDRESS_RANGE_1_REG_ECC_END_ADDR_1,
                          endAddr);
            /*Enable/Disable ECC address range 1*/
            HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                          EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_1_EN,
                          pAddrRangeCfgPrm->enableAddrRange);
        }

        /*Configs EMIF ECC Addr Range is within /Outside defined Addr range*/
        HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                      EMIF_ECC_CTRL_REG_REG_ECC_ADDR_RGN_PROT,
                      pAddrRangeCfgPrm->addrRangeType);

        /*Configure the thresholds to generate 1-bit error interrupt*/
        HW_WR_FIELD32(baseAddr + EMIF_1B_ECC_ERR_THRSH,
                      EMIF_1B_ECC_ERR_THRSH_REG_1B_ECC_ERR_THRSH,
                      pCfgPrm->thresholdVal);
    #if defined (SOC_TDA2PX)
        if(pCfgPrm->enableRmw == 0U)
        {
            /*Configure the RMW for sub quanta access */
            HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                        EMIF_ECC_CTRL_REG_REG_RMW_EN, 0U);
        }
        else
        {
            /*Configure the RMW for sub quanta access */
            HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                        EMIF_ECC_CTRL_REG_REG_RMW_EN, 1U);
        }
    #endif
    }

    return retVal;
}

void EMIFConfigECCEnableEcc(uint32_t baseAddr)
{
    /*Enable EMIF ECC*/
    HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                  EMIF_ECC_CTRL_REG_REG_ECC_EN,
                  EMIF_ECC_ENABLE);
}

void EMIFConfigECCDisableEcc(uint32_t baseAddr)
{
    /*Disable EMIF ECC*/
    HW_WR_FIELD32(baseAddr + EMIF_ECC_CTRL_REG,
                  EMIF_ECC_CTRL_REG_REG_ECC_EN,
                  EMIF_ECC_DISABLE);
}

void EMIFEnableIntr(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_SET, intrMask);
}

void EMIFDisableIntr(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_ENABLE_CLEAR, intrMask);
}

uint32_t EMIFGetIntrStatus(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_STATUS));
}

void EMIFClearIntrStatus(uint32_t baseAddr, uint32_t intrMask)
{
    HW_WR_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_STATUS, intrMask);
}

uint32_t EMIFGetIntrRawStatus(uint32_t baseAddr)
{
    return (HW_RD_REG32(baseAddr + EMIF_SYSTEM_OCP_INTERRUPT_RAW_STATUS));
}

int32_t EMIFConfigECCGetEccErrInfo(uint32_t          baseAddr,
                                   uint32_t          errType,
                                   emifEccErrInfo_t *pErrInfo)
{
    uint32_t fifoIndex = 0;
    int32_t  retVal    = STW_SOK;

    if (pErrInfo == NULL)
    {
        retVal = STW_EFAIL;
    }
    else
    {
        if ((errType & EMIF_ERR_ECC_ONEBIT) == EMIF_ERR_ECC_ONEBIT)
        {
            /* Reads ECC Err count and clears ECC Err count*/
            pErrInfo->errCnt = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_CNT);
            HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_CNT),
                        pErrInfo->errCnt);

            /* Reads ECC Err Bit mask and clears ECC Err Bit mask*/
            pErrInfo->errBitLoc = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_DIST_1);
            HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_DIST_1),
                        pErrInfo->errBitLoc);

            if (pErrInfo->errCnt > EMIF_ECC_FIFO_BUF_SIZE)
            {
                /* Address log FIFO Buffer is overflowed*/
                pErrInfo->numValidErrAddr = EMIF_ECC_FIFO_BUF_SIZE;
            }
            else
            {
                pErrInfo->numValidErrAddr = pErrInfo->errCnt;
            }

            while (fifoIndex < pErrInfo->numValidErrAddr)
            {
                /* Reads ECC Err Addr log and clears ECC Err Addr log reg and
                 * Address log Fifo Buffer */
                pErrInfo->errAddr[fifoIndex] =
                    HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_ADDR_LOG);
                HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_ADDR_LOG), 0x1);
                fifoIndex++;
            }
        }
        else if ((errType & EMIF_ERR_ECC_TWOBIT) == EMIF_ERR_ECC_TWOBIT)
        {
            /* Reads ECC Err Addr log and clears ECC Err Addr log reg and
             * Address log Fifo Buffer */
            pErrInfo->errAddr[fifoIndex] =
                HW_RD_REG32(baseAddr + EMIF_2B_ECC_ERR_ADDR_LOG);
            HW_WR_REG32((baseAddr + EMIF_2B_ECC_ERR_ADDR_LOG), 0x1);
        }
        else
        {
            /* Nothing */
        }
    }

    return retVal;
}

void EMIFConfigECCClrAllEccErrInfo(uint32_t baseAddr)
{
    uint32_t regVal;
    uint32_t errCnt;
    uint32_t numValidErrAddr;

    /* Clears 1Bit ECC Err Info*/
    errCnt = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_CNT);
    HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_CNT), errCnt);

    regVal = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_DIST_1);
    HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_DIST_1), regVal);

    if (errCnt > EMIF_ECC_FIFO_BUF_SIZE)
    {
        /* Adress log FIFO Buffer is overflowed*/
        numValidErrAddr = EMIF_ECC_FIFO_BUF_SIZE;
    }
    else
    {
        numValidErrAddr = errCnt;
    }

    while (numValidErrAddr)
    {
        regVal = HW_RD_REG32(baseAddr + EMIF_1B_ECC_ERR_ADDR_LOG);
        HW_WR_REG32((baseAddr + EMIF_1B_ECC_ERR_ADDR_LOG), 0x1);
        numValidErrAddr = numValidErrAddr - 1U;
    }

    /* Clears 2Bit ECC Err Info*/
    regVal = HW_RD_REG32(baseAddr + EMIF_2B_ECC_ERR_ADDR_LOG);
    HW_WR_REG32((baseAddr + EMIF_2B_ECC_ERR_ADDR_LOG), 0x1);
}
