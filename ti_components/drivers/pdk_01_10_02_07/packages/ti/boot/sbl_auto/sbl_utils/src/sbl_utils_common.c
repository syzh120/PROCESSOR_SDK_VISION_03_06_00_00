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
 *  \file     sbl_utils_common.c
 *
 *  \brief    This file contains the SBL Utility layer common across platforms.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <string.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_common.h>
#include <sbl_utils_priv.h>
#include <ti/drv/stw_lld/uartconsole/uartConsole.h>
#if defined (SOC_TDA3XX)
#include <ti/boot/sbl_auto/sbl_utils/sbl_utils_tda3xx.h>
#endif

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

/* Zero array used in priming ECC protected memory */
static volatile uint32_t gEmifEccInitBuff[32U] = {0U};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

uint32_t SBLUtilsRead32KTimer(void)
{
    uint32_t timerVal = 0U;

    /* Read the counter value for 32 KHz SoC Synchronous Timer */
    timerVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);

    return timerVal;
}

int32_t SBLUtilsPrintfInit(UART_INST_t uartInstance)
{
    int32_t retVal = STW_SOK;

    /* Configure PRCM for UART instance */
    retVal = SBLUtilsUartPrcm(uartInstance);
    if (STW_SOK != retVal)
    {
        SBLLibAbortBoot();
    }

    /* Configure Pin Mux for UART instance */
    SBLLibConfigureUARTPinMux(uartInstance);

    /* Initialize UART Peripheral */
    UARTConsoleInit(uartInstance);

    return retVal;
}

void SBLUtilsTriggerEDMAPolledMode(uint32_t srcAddr,
                                   uint32_t destAddr,
                                   uint32_t dataSize,
                                   uint32_t edmaChannelNum,
                                   uint32_t edmaTccNum,
                                   uint32_t edmaEvtqNum,
                                   uint32_t paramSetNum)
{
    EDMA3CCPaRAMEntry edmaParams;
    uint32_t          edmaACnt, edmaBCnt, edmaCCnt;
    uint32_t          tempdataSize = dataSize;
    uint32_t          remDataSize;
    uint32_t          idx;

    /*
     * EDMA transfer is of type AB synchronized for better throughput.
     * Set ACnt as 64 bytes and calculate BCnt & CCnt.
     */
    edmaACnt = 0x3FF0U;
    edmaCCnt = 1U;
    while (0xFFFFU < (tempdataSize / edmaACnt))
    {
        edmaCCnt     = edmaCCnt * 2U;
        tempdataSize = tempdataSize / 2U;
    }
    edmaBCnt     = tempdataSize / edmaACnt;
    tempdataSize = edmaACnt * edmaBCnt * edmaCCnt;
    remDataSize  = dataSize - tempdataSize;

    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNum,
                        edmaTccNum,
                        edmaEvtqNum);

    edmaParams.opt      = 0U;
    edmaParams.srcAddr  = srcAddr;
    edmaParams.destAddr = destAddr;
    edmaParams.aCnt     = edmaACnt;
    edmaParams.bCnt     = edmaBCnt;
    edmaParams.cCnt     = edmaCCnt;
    edmaParams.srcBIdx  = edmaACnt;
    edmaParams.destBIdx = edmaACnt;
    edmaParams.srcCIdx  = edmaACnt * edmaBCnt;
    edmaParams.destCIdx = edmaACnt * edmaBCnt;
    edmaParams.linkAddr = 0xFFFFU;
    /* Program the TCC */
    edmaParams.opt |=
        ((edmaTccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);
    /* Enable Intermediate & Final transfer completion interrupt */
    edmaParams.opt |= (EDMA3_OPT_ITCINTEN_MASK);
    edmaParams.opt |= (EDMA3_OPT_TCINTEN_MASK);
    /* AB Sync Transfer Mode */
    edmaParams.opt |= EDMA_TPCC_OPT_SYNCDIM_MASK;

    /* Map Param Set to Channel */
    EDMA3ChannelToParamMap(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNum, paramSetNum);

    /* Set Params in EDMA registers */
    EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, paramSetNum, &edmaParams);

    /*
     * Transfer is done in AB sync mode
     * Number of triggers required are edmaCCnt
     */
    for (idx = 0U; idx < edmaCCnt; idx++)
    {
        /* Enable transfer manually */
        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNum,
                            EDMA3_TRIG_MODE_MANUAL);

        /* Wait for transfer to complete */
        while (((uint32_t) 0x1U << edmaTccNum) !=
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                ((uint32_t) 0x1U << edmaTccNum)))
        {
            /* Busy Loop */
        }

        /* Clear EDMA completion interrupt */
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTccNum);
    }

    if (0U != remDataSize)
    {
        edmaParams.opt      = 0U;
        edmaParams.srcAddr  = srcAddr + ((edmaACnt * edmaBCnt) * edmaCCnt);
        edmaParams.destAddr = destAddr + ((edmaACnt * edmaBCnt) * edmaCCnt);
        edmaParams.aCnt     = remDataSize;
        edmaParams.bCnt     = 1U;
        edmaParams.cCnt     = 1U;
        edmaParams.srcBIdx  = remDataSize;
        edmaParams.destBIdx = remDataSize;
        edmaParams.srcCIdx  = 0U;
        edmaParams.destCIdx = 0U;
        edmaParams.linkAddr = 0xFFFFU;
        edmaParams.opt     |=
            (EDMA3_OPT_TCINTEN_MASK |
             ((edmaTccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK));

        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, paramSetNum, &edmaParams);

        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNum,
                            EDMA3_TRIG_MODE_MANUAL);

        while (((uint32_t) 0x1U << edmaTccNum) !=
               (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                ((uint32_t) 0x1U << edmaTccNum)))
        {
            /* Busy Loop */
        }
        EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTccNum);
    }
}

int32_t SBLUtilsEmifECCConfigure(void)
{
    /* Before configuring ECC EMIF, make sure ECC is enabled in control module
     * i.e. register CTRL_WKUP_EMIF1_SDRAM_CONFIG_EXT
     */
    int32_t                  retVal = STW_SOK;
    emifEccCfgPrm_t          eccConfigParams;
    emifEccAddrRangeCfgPrm_t addrRangeParams[2U];
    uint32_t                 edmaStartAddr1, edmaEndAddr1;
    uint32_t                 edmaStartAddr2, edmaEndAddr2;
    uint32_t                 edmaStartAddr3, edmaEndAddr3;
    uint32_t                 srcBuffAddr, intrStatus;
    uint32_t                 range1Type, range1StartAddr, range1EndAddr;
    uint32_t                 range2Type, range2StartAddr, range2EndAddr;
    uint32_t                 emif1Size;

    memset(&eccConfigParams, 0, sizeof (eccConfigParams));
    memset(&addrRangeParams, 0, sizeof (addrRangeParams));

    emif1Size = SBLUtilsGetEmif1Size();

    SBLUtilsGetECCAddrRangePrms((emifEccAddrRangeCfgPrm_t *) &addrRangeParams);
    range1Type      = addrRangeParams[0U].addrRangeType;
    range1StartAddr = addrRangeParams[0U].startAddr;
    range1EndAddr   = addrRangeParams[0U].endAddr;
    range2Type      = addrRangeParams[1U].addrRangeType;
    range2StartAddr = addrRangeParams[1U].startAddr;
    range2EndAddr   = addrRangeParams[1U].endAddr;

    /* Configure EMIF ECC parameters common for region1 and region 2 */
    eccConfigParams.thresholdVal  = 0x1U;
    eccConfigParams.emifStartAddr = SBL_LIB_CONFIG_EMIF_START_ADDR;

    /* Enable ECC for Region1 */
    eccConfigParams.addrRangeCfgPrm = &addrRangeParams[0U];
    if ((0U != eccConfigParams.addrRangeCfgPrm->startAddr) &&
        (0U != eccConfigParams.addrRangeCfgPrm->endAddr))
    {
        retVal += EMIFConfigECCInitECCParams(SOC_EMIF1_CONF_REGS_BASE,
                                             &eccConfigParams);
    }

    /* Enable ECC for Region2 */
    eccConfigParams.addrRangeCfgPrm = &addrRangeParams[1U];
    if ((0U != eccConfigParams.addrRangeCfgPrm->startAddr) &&
        (0U != eccConfigParams.addrRangeCfgPrm->endAddr))
    {
        retVal += EMIFConfigECCInitECCParams(SOC_EMIF1_CONF_REGS_BASE,
                                             &eccConfigParams);
    }

    /* Enable EMIF ECC */
    EMIFConfigECCEnableEcc(SOC_EMIF1_CONF_REGS_BASE);

    /* Initialize the EDMA */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

    srcBuffAddr = (uint32_t) (gEmifEccInitBuff) + 0x40000000U;

    /* Initialize ECC EMIF Regions */
    if ((EMIF_ECC_ADDR_RANGE_WITHIN == range1Type) &&
        (EMIF_ECC_ADDR_RANGE_WITHIN == range2Type))
    {
        SBLUtilsPreFillECCMemory((const void *) range1StartAddr,
                                 (const void *) srcBuffAddr,
                                 ((range1EndAddr - range1StartAddr) + 1U));

        SBLUtilsPreFillECCMemory((const void *) range2StartAddr,
                                 (const void *) srcBuffAddr,
                                 ((range2EndAddr - range2StartAddr) + 1U));
    }
    else if ((EMIF_ECC_ADDR_RANGE_WITHIN !=
              addrRangeParams[0U].addrRangeType) &&
             (EMIF_ECC_ADDR_RANGE_WITHIN == range2Type))
    {
        edmaStartAddr1 = SBL_LIB_CONFIG_EMIF_START_ADDR;
        edmaEndAddr1   = range1StartAddr;
        if (edmaStartAddr1 != edmaEndAddr1)
        {
            SBLUtilsPreFillECCMemory((const void *) edmaStartAddr1,
                                     (const void *) srcBuffAddr,
                                     ((edmaEndAddr1 - edmaStartAddr1) + 1U));
        }
        edmaStartAddr2 = range1EndAddr;
        edmaEndAddr2   = emif1Size + SBL_LIB_CONFIG_EMIF_START_ADDR;
        SBLUtilsPreFillECCMemory((const void *) edmaStartAddr2,
                                 (const void *) srcBuffAddr,
                                 ((edmaEndAddr2 - edmaStartAddr2) + 1U));
    }
    else if ((EMIF_ECC_ADDR_RANGE_WITHIN == range1Type) &&
             (EMIF_ECC_ADDR_RANGE_WITHIN != range2Type))
    {
        edmaStartAddr1 = SBL_LIB_CONFIG_EMIF_START_ADDR;
        edmaEndAddr1   = range2StartAddr;
        if (edmaStartAddr1 != edmaEndAddr1)
        {
            SBLUtilsPreFillECCMemory((const void *) edmaStartAddr1,
                                     (const void *) srcBuffAddr,
                                     ((edmaEndAddr1 - edmaStartAddr1) + 1U));
        }
        edmaStartAddr2 = range2EndAddr;
        edmaEndAddr2   = emif1Size + SBL_LIB_CONFIG_EMIF_START_ADDR;
        SBLUtilsPreFillECCMemory((const void *) edmaStartAddr2,
                                 (const void *) srcBuffAddr,
                                 ((edmaEndAddr2 - edmaStartAddr2) + 1U));
    }
    else /*(EMIF_ECC_ADDR_RANGE_WITHIN != range1Type) &&
          * (EMIF_ECC_ADDR_RANGE_WITHIN != range2Type) */
    {
        edmaStartAddr1 = SBL_LIB_CONFIG_EMIF_START_ADDR;
        edmaEndAddr1   = range1StartAddr;
        if (edmaStartAddr1 != edmaEndAddr1)
        {
            SBLUtilsPreFillECCMemory((const void *) edmaStartAddr1,
                                     (const void *) srcBuffAddr,
                                     ((edmaEndAddr1 - edmaStartAddr1) + 1U));
        }
        edmaStartAddr2 = range1EndAddr;
        edmaEndAddr2   = range2StartAddr;
        SBLUtilsPreFillECCMemory((const void *) edmaStartAddr2,
                                 (const void *) srcBuffAddr,
                                 ((edmaEndAddr2 - edmaStartAddr2) + 1U));
        edmaStartAddr3 = range2EndAddr;
        edmaEndAddr3   = emif1Size + SBL_LIB_CONFIG_EMIF_START_ADDR;
        SBLUtilsPreFillECCMemory((const void *) edmaStartAddr3,
                                 (const void *) srcBuffAddr,
                                 ((edmaEndAddr3 - edmaStartAddr3) + 1U));
    }

    /* De-initialize EDMA */
    EDMA3Deinit(SOC_EDMA_TPCC_BASE_VIRT, 0);

    /* Check for ECC errors before loading app image */
    intrStatus = EMIFGetIntrRawStatus(SOC_EMIF1_CONF_REGS_BASE);
    if (0U != intrStatus)
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            " EMIF ECC violation occurred before loading app image, aborting boot");
        SBLLibAbortBoot();
    }

    return retVal;
}

void SBLUtilsPreFillECCMemory(const void *eccMemStartAddr,
                              const void *srcBuffAddr,
                              uint32_t    memSize)
{
    EDMA3CCPaRAMEntry edmaParams;
    uint32_t          edmaACnt, edmaBCnt, edmaCCnt;
    uint32_t          edmaChannelNum = 1U, edmaTccNum = 1U;
    uint32_t          edmaEvtqNum    = 0U, paramSetNum = 1U;
    uint32_t          tempdataSize   = memSize;
    uint32_t          remDataSize    = 0U, maxBCnt = 0xFFU;
    uint32_t          idx, remBytes = 0U;

    if (NULL != eccMemStartAddr)
    {
        /*
         * EDMA transfer is of type AB synchronized for better throughput.
         * Set ACnt as 128 bytes and calculate BCnt & CCnt.
         */
        /* remDataSize takes care of data which is multiple of 128 bytes and
         * remBytes take of the remaining Bytes
         */
        edmaACnt = 128U;
        edmaBCnt = tempdataSize / edmaACnt;
        remBytes = tempdataSize % edmaACnt;
        edmaCCnt = 1U;
        if (edmaBCnt > maxBCnt)
        {
            edmaCCnt    = tempdataSize / (maxBCnt * edmaACnt);
            edmaBCnt    = maxBCnt;
            remDataSize = tempdataSize - (edmaACnt * (edmaBCnt * edmaCCnt));
        }

        /* Request EDMA Channel */
        EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                            EDMA3_CHANNEL_TYPE_DMA,
                            edmaChannelNum,
                            edmaTccNum,
                            edmaEvtqNum);

        /* Set EDMA parameters */
        edmaParams.opt      = 0U;
        edmaParams.srcAddr  = (uint32_t) srcBuffAddr;
        edmaParams.destAddr = (uint32_t) eccMemStartAddr;
        edmaParams.aCnt     = edmaACnt;
        edmaParams.bCnt     = edmaBCnt;
        edmaParams.cCnt     = edmaCCnt;
        edmaParams.srcBIdx  = 0U;
        edmaParams.destBIdx = edmaACnt;
        edmaParams.srcCIdx  = 0U;
        edmaParams.destCIdx = edmaACnt * edmaBCnt;
        edmaParams.linkAddr = 0xFFFFU;
        /* Program the TCC */
        edmaParams.opt |=
            ((edmaTccNum << EDMA_TPCC_OPT_TCC_SHIFT) & EDMA_TPCC_OPT_TCC_MASK);
        /* Enable Intermediate & Final transfer completion interrupt */
        edmaParams.opt |= (EDMA3_OPT_ITCINTEN_MASK);
        edmaParams.opt |= (EDMA3_OPT_TCINTEN_MASK);
        /* AB Sync Transfer Mode */
        edmaParams.opt |= EDMA_TPCC_OPT_SYNCDIM_MASK;

        /* Map Param Set to Channel */
        EDMA3ChannelToParamMap(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNum, paramSetNum);

        /* Set Params in EDMA registers */
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, paramSetNum, &edmaParams);

        /*
         * Transfer is done in AB sync mode
         * Number of triggers required are edmaCCnt
         */
        for (idx = 0U; idx < edmaCCnt; idx++)
        {
            /* Enable transfer manually */
            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                                edmaChannelNum,
                                EDMA3_TRIG_MODE_MANUAL);

            /* Wait for transfer to complete */
            while (((uint32_t) 0x1U << edmaTccNum) !=
                   (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                    ((uint32_t) 0x1U << edmaTccNum)))
            {
                /* Busy Loop */
            }

            /* Clear EDMA completion interrupt */
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTccNum);
        }

        if (0U != remDataSize)
        {
            edmaParams.opt      = 0U;
            edmaParams.srcAddr  = (uint32_t) srcBuffAddr;
            edmaParams.destAddr = (uint32_t) eccMemStartAddr +
                                  ((edmaACnt * edmaBCnt) * edmaCCnt);
            edmaParams.aCnt     = edmaACnt;
            edmaParams.bCnt     = remDataSize / edmaACnt;
            edmaParams.cCnt     = 1U;
            edmaParams.srcBIdx  = 0U;
            edmaParams.destBIdx = edmaACnt;
            edmaParams.srcCIdx  = 0U;
            edmaParams.destCIdx = 0U;
            edmaParams.linkAddr = 0xFFFFU;
            edmaParams.opt      =
                (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
                 EDMA3_OPT_ITCINTEN_MASK |
                 ((edmaTccNum << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

            EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, paramSetNum, &edmaParams);

            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNum,
                                EDMA3_TRIG_MODE_MANUAL);

            while (((uint32_t) 0x1U << edmaTccNum) !=
                   (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                    ((uint32_t) 0x1U << edmaTccNum)))
            {
                /* Busy Loop */
            }
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTccNum);
        }

        if (0U != remBytes)
        {
            edmaParams.opt      = 0U;
            edmaParams.srcAddr  = (uint32_t) srcBuffAddr;
            edmaParams.destAddr = (uint32_t) eccMemStartAddr +
                                  ((edmaACnt * edmaBCnt) * edmaCCnt) +
                                  (edmaParams.aCnt * edmaParams.bCnt);
            edmaParams.aCnt     = remBytes;
            edmaParams.bCnt     = 1U;
            edmaParams.cCnt     = 1U;
            edmaParams.srcBIdx  = 0U;
            edmaParams.destBIdx = 0U;
            edmaParams.srcCIdx  = 0U;
            edmaParams.destCIdx = 0U;
            edmaParams.linkAddr = 0xFFFFU;
            edmaParams.opt      =
                (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
                 EDMA3_OPT_ITCINTEN_MASK |
                 ((edmaTccNum << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));

            EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, paramSetNum, &edmaParams);

            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNum,
                                EDMA3_TRIG_MODE_MANUAL);

            while (((uint32_t) 0x1U << edmaTccNum) !=
                   (EDMA3GetIntrStatus(SOC_EDMA_TPCC_BASE_VIRT) &
                    ((uint32_t) 0x1U << edmaTccNum)))
            {
                /* Busy Loop */
            }
            EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTccNum);
        }
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

