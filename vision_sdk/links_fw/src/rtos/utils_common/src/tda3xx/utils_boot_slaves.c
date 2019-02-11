/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 * \file utils_slave_boot.c
 *
 * \brief  This file has the implementataion for booting slave cores using
 *         SBL LIB
 *
 * \version 0.0 (Jun 2015) : [YM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
#include <string.h>
#include <ti/csl/csl_crc.h>
#include <ti/csl/csl_qspi.h>
#include <ti/csl/soc.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_tda3xx.h>
#include <ti/drv/pm/pmlib.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/sysbios/hal/Cache.h>

#define UTILS_BOOT_SLAVES_DEBUG (0U)
#define MIN_SIZE_DMA_TRANSFER   (1024U)


#include <src/rtos/utils_common/include/utils_qspi.h>
#include <src/rtos/utils_common/include/utils_idle.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include <src/rtos/utils_common/include/utils_mem_cfg.h>
#include <src/rtos/utils_common/include/utils_boot_slaves.h>
#include <src/rtos/links_common/system/system_priv_ipc.h>
#include <ti/sysbios/hal/Cache.h>

sbllibMetaHeaderV2_t           sblAppMetaHeaderV2;
sbllibRPRCImageHeader_t        sblAppRPRCHeader;
Utils_DmaChObj                 gDumpSectionsDmaObj;
static sbllibEntryPoints_t     gSblLibEntryPoints;

static UInt32 gMaxDdrBuffSize;
static UInt32 gDDRBaseAddr;
static UInt32 gDsp1L2ramSaveDdrAddress = 0U, gDsp2L2ramSaveDdrAddress = 0U;

/*******************************************************************************
 *  Local Function Declarations
 *******************************************************************************
 */
static Int32 Utils_qspiReadSectorsEdma(Void       *dstAddr,
                                       UInt32 srcOffsetAddr,
                                       UInt32      length);

static Int32 Utils_ddrReadEdma(Void   *dstAddr,
                               UInt32  srcAddr,
                               UInt32  length);

static Int32 Utils_computeCRC(const void     *crcSrcAddr,
                              UInt32          crcDataSize,
                              crcSignature_t *crcSignVal);

static Int32 Utils_ddrReadMemCpy(Void   *dstAddr,
                                 UInt32  srcAddr,
                                 UInt32  length);

static Int32 Utils_qspiReadSectorsMemCpy(Void       *dstAddr,
                                         UInt32 srcOffsetAddr,
                                         UInt32      length);
static void Utils_printFxn(const char* msg);
Void Utils_syncSlaves(void);

static Int32 Utils_qspiReadSectorsEdma(Void       *dstAddr,
                                       UInt32 srcOffsetAddr,
                                       UInt32      length)
{
    Int32 status = EDMA3_DRV_SOK;
    UInt32 tempAddrOffset;
    Utils_DmaCopy1D dmaPrm;

    /* dstAddr is the start address of the buffer, hence following condition
     * is sufficient.
     */
    UTILS_assert(length <= gMaxDdrBuffSize);

    if(length < MIN_SIZE_DMA_TRANSFER)
    {
        QSPI_ReadSectors(dstAddr, srcOffsetAddr, length);
    }
    else
    {
        dmaPrm.destAddr = dstAddr;
        tempAddrOffset = SOC_QSPI_ADDRSP1_BASE + srcOffsetAddr;

        /* MISRA.CAST.PTR_TO_INT: MISRAC_2004 Rule_11.3
         * Memory mapped register typecasted to pointer for the dma copy.
         * there is no check for the srcOffsetAddr as it is added to
         * SOC_QSPI_ADDRSP1_BASE to get the final address.
         */
        dmaPrm.srcAddr  = (Ptr)tempAddrOffset;
        dmaPrm.length   = length;

        status = Utils_dmaCopy1D(&gDumpSectionsDmaObj, &dmaPrm);
        UTILS_assert(status == EDMA3_DRV_SOK);

        /* Ensure that the M4 does not have a stale copy of the region
         * to which the copy is being made.
         */
        Cache_inv(dstAddr, length, Cache_Type_ALL, (Bool)TRUE);
    }


    #if UTILS_BOOT_SLAVES_DEBUG
    Vps_printf(" UTILS: BOOT SLAVES: section dst [0x%x] src [0x%x] length [0x%x]",
                 dstAddr, (SOC_QSPI_ADDRSP1_BASE + srcOffsetAddr), length);
    #endif

    return status;
}

static Int32 Utils_computeCRC(const void     *crcSrcAddr,
                              UInt32          crcDataSize,
                              crcSignature_t *crcSignVal)
{
    EDMA3_DRV_Result edma3Result = EDMA3_DRV_SOK;
    EDMA3_DRV_PaRAMRegs *pParamSet;
    crcSignatureRegAddr_t crcSignRegAddr;
    UInt32 crcPatternSize  = 0U, crcPatternCount = 0U, crcSectorCount = 0U;
    UInt32 edmaACnt        = 0U, edmaBCnt = 0U, edmaCCnt = 0U;
    UInt32 remBytes        = 0U;
    UInt32 maxPatternCount = 0xFFFFFU, maxBCnt = 0xFFFU;
    UInt32 origDataSize    = 0U, remPatternCount = 0U;
    UInt32 iterCount       = 0U, iterIndex = 0U, dataRead = 0U;
    UInt32 opt = 0U;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule 11.3
     * MISRAC_WAIVER:  Typecasting srcAddr to UInt as Cache_wb expects
     * source address in Void * whereas passed source address is in const addr *
     * format. Expectation of both
     * of these params are different, so to fix MisraC issue, typecasting it to
     * UInt and then using this variable.
     */
    UInt32 crcSrvAddrInUint = (UInt32)crcSrcAddr;

    if ((NULL == crcSrcAddr) || (NULL == crcSignVal))
    {
        edma3Result =  -(Int32)1;
    }
    else
    {
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004 Rule 11.3
         * MISRAC_WAIVER:  Typecasting uint to void * as expected by
         * cache_wb API. There is an already check to make sure passed
         * src address is not null.
         */
        /* Ensure that the EMDA has the latest copy of the region
         * for which CRC needs to be calculated.
         */
        Cache_wb((Void *)crcSrvAddrInUint, crcDataSize, Cache_Type_ALL, (Bool)TRUE);

        /* Initialize CRC signature value to zero */
        crcSignVal->regL = 0U;
        crcSignVal->regH = 0U;

        /* Get CRC PSA signature register address */
        CRCGetPSASigRegAddr(SOC_CRC_BASE, CRC_CHANNEL_1, &crcSignRegAddr);

        /* Initialize CRC channel */
        edma3Result += CRCInitialize(SOC_CRC_BASE, CRC_CHANNEL_1, 0x0U, 0x0U);

        BspOsal_semWait(gDumpSectionsDmaObj.semLock, BSP_OSAL_WAIT_FOREVER);

        /* Set CRC signature Seed value to Zero */
        CRCSetPSASeedSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);

        crcPatternSize  = 8U;
        crcSectorCount  = 1U;
        crcPatternCount = crcDataSize / crcPatternSize;
        origDataSize    = crcDataSize;

        /* Max CRC pattern count value can be 0xFFFFFU */
        if (maxPatternCount < crcPatternCount)
        {
            iterCount       = origDataSize / (maxPatternCount * crcPatternSize);
            remPatternCount =
                (origDataSize -
                 (iterCount * (maxPatternCount * crcPatternSize))) / crcPatternSize;
            crcPatternCount = maxPatternCount;
        }

        for (iterIndex = 0U; iterIndex <= iterCount; iterIndex++)
        {
            if ((iterIndex == iterCount) && (0U < iterCount))
            {
                crcPatternCount = remPatternCount;
            }

            if (0U < iterIndex)
            {
                /* Fetch CRC signature and clear interrupt status */
                while (0x0U == CRCGetIntrStatus(SOC_CRC_BASE, CRC_CHANNEL_1))
                {
                    /* Do Nothing */
                }

                /* Fetch CRC signature value */
                CRCGetPSASectorSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);

                /* Clear CRC Interrupt Status */
                CRCClearIntr(SOC_CRC_BASE,
                             CRC_CHANNEL_1,
                             CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);

                /* Set CRC signature Seed value */
                CRCSetPSASeedSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);
            }

            crcDataSize = crcPatternCount * crcPatternSize;

            /* Configure CRC channel */
            edma3Result += CRCConfigure(SOC_CRC_BASE,
                                   CRC_CHANNEL_1,
                                   crcPatternCount,
                                   crcSectorCount,
                                   CRC_OPERATION_MODE_SEMICPU);

            edmaACnt = crcPatternSize;
            edmaBCnt = crcDataSize / edmaACnt;
            edmaCCnt = 1U;
            if (edmaBCnt > maxBCnt)
            {
                edmaCCnt = crcDataSize / (maxBCnt * edmaACnt);
                edmaBCnt = maxBCnt;
                remBytes = crcDataSize - (edmaACnt * (edmaBCnt * edmaCCnt));
            }

            /* Set EDMA parameters */
            pParamSet             = gDumpSectionsDmaObj.txObj[0].pParamSet;
            pParamSet->opt        = 0;

            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004 Rule 11.3
             * MISRAC_WAIVER:  Typecasting crcAddr from void * to uint
             * as expected by edma params set. There is a check to make
             * sure that address is not null. Also Added dataRead bytes
             * never goes out of allocated memory for CRC.
             */
            pParamSet->srcAddr    = (UInt32) crcSrcAddr + dataRead;
            pParamSet->destAddr   = crcSignRegAddr.regL;
            pParamSet->aCnt       = edmaACnt;
            pParamSet->bCnt       = edmaBCnt;
            pParamSet->cCnt       = edmaCCnt;
            pParamSet->srcBIdx    = pParamSet->aCnt;
            pParamSet->destBIdx   = 0;
            pParamSet->srcCIdx    = pParamSet->aCnt * pParamSet->bCnt;
            pParamSet->destCIdx   = 0;
            pParamSet->linkAddr   = 0xFFFF;
            opt  =
                    ((UInt32)((UInt32)EDMA3_CCRL_OPT_ITCCHEN_ENABLE << EDMA3_CCRL_OPT_ITCCHEN_SHIFT))
                | ((UInt32)((UInt32)gDumpSectionsDmaObj.tccId << EDMA3_CCRL_OPT_TCC_SHIFT)
                            & EDMA3_CCRL_OPT_TCC_MASK
                    )
                | ((UInt32)((UInt32)EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT));
            /* enable interrupt for last Transfer ONLY */
            opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_TCINTEN_ENABLE
                        << EDMA3_CCRL_OPT_TCINTEN_SHIFT);

            pParamSet->opt = opt;

            /* Trigger the EDMA */
            edma3Result = Utils_dmaTriggerAndWait(&gDumpSectionsDmaObj);

            if (edma3Result != EDMA3_DRV_SOK)
            {
                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004 Rule 11.3
                 * MISRAC_WAIVER:  Typecasting crcAddr from void * to uint
                 * as printing address. There is a check to make
                 * sure that address is not null. Also Added dataRead bytes
                 * never goes out of allocated memory for CRC.
                 */
                Vps_printf(
                    " UTILS: BOOT SLAVES: Utils_computeCRC() Failed; Address:[0x%x] Size:[0x%x] \n",
                        (UInt32) crcSrcAddr + dataRead, crcDataSize
                    );
            }
            dataRead += ((edmaACnt * edmaBCnt) * edmaCCnt);

            if ((0U != remBytes) && (EDMA3_DRV_SOK == edma3Result))
            {
                /* Set EDMA parameters */
                pParamSet->opt        = 0;

                /* MISRA.CAST.PTR_TO_INT
                 * MISRAC_2004 Rule 11.3
                 * MISRAC_WAIVER:  Typecasting crcAddr from void * to uint
                 * as expected by edma params set. There is a check to make
                 * sure that address is not null. Also Added dataRead bytes
                 * never goes out of allocated memory for CRC.
                 */
                pParamSet->srcAddr    = (UInt32) crcSrcAddr + dataRead;
                pParamSet->destAddr   = crcSignRegAddr.regL;
                pParamSet->aCnt       = edmaACnt;
                pParamSet->bCnt       = remBytes / edmaACnt;
                pParamSet->cCnt       = 1;
                pParamSet->srcBIdx    = pParamSet->aCnt;
                pParamSet->destBIdx   = 0;
                pParamSet->srcCIdx    = pParamSet->aCnt * pParamSet->bCnt;
                pParamSet->destCIdx   = 0;
                pParamSet->linkAddr   = 0xFFFF;
                opt  =
                        ((UInt32)((UInt32)EDMA3_CCRL_OPT_ITCCHEN_ENABLE << EDMA3_CCRL_OPT_ITCCHEN_SHIFT))
                    | ((UInt32)((UInt32)gDumpSectionsDmaObj.tccId << EDMA3_CCRL_OPT_TCC_SHIFT)
                                & EDMA3_CCRL_OPT_TCC_MASK
                        )
                    | ((UInt32)((UInt32)EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT))
                        ;
                /* enable interrupt for last Transfer ONLY */
                opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_TCINTEN_ENABLE
                            << EDMA3_CCRL_OPT_TCINTEN_SHIFT);

                pParamSet->opt = opt;

                edma3Result = Utils_dmaTriggerAndWait(&gDumpSectionsDmaObj);
                if (edma3Result != EDMA3_DRV_SOK)
                {
                    /* MISRA.CAST.PTR_TO_INT
                     * MISRAC_2004 Rule 11.3
                     * MISRAC_WAIVER:  Typecasting crcAddr from void * to uint
                     * as printing address. There is a check to make
                     * sure that address is not null. Also Added dataRead bytes
                     * never goes out of allocated memory for CRC.
                     */
                    Vps_printf(
                    " UTILS: BOOT SLAVES: Utils_computeCRC() Failed for remBytes; Address:[0x%x] Size:[0x%x] \n",
                        (UInt32) crcSrcAddr + dataRead, remBytes
                    );
                }
                dataRead += remBytes;
                remBytes = 0U;
            }
        }

        /* Fetch CRC signature and clear interrupt status */
        while (0x0U == CRCGetIntrStatus(SOC_CRC_BASE, CRC_CHANNEL_1))
        {
            /* Do Nothing */
        }

        /* Fetch CRC signature value */
        CRCGetPSASectorSig(SOC_CRC_BASE, CRC_CHANNEL_1, crcSignVal);

        /* Clear CRC Interrupt Status */
        CRCClearIntr(SOC_CRC_BASE,
                     CRC_CHANNEL_1,
                     CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);

        if ((dataRead != origDataSize))
        {
            Vps_printf(
                    " UTILS: BOOT SLAVES: Utils_computeCRC() Failed: Incomplete EDMA \n"
                    );
        }

        BspOsal_semPost(gDumpSectionsDmaObj.semLock);
    }

    return edma3Result;
}

static Int32 Utils_ddrReadEdma(Void   *dstAddr,
                               UInt32  srcAddr,
                               UInt32  length)
{
    Int32 status = EDMA3_DRV_SOK;
    Utils_DmaCopy1D dmaPrm;
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule 11.3
     * MISRAC_WAIVER:  Typecasting srcAddr to UInt as dmaPrm expects srcAddr
     * in Ptr whereas passed src address is const void *. Expectation of both
     * of these params are different, so to fix MisraC issue, typecasting it to
     * UInt and then using this variable.
     */
    UInt32 srcAddrInUInt = (UInt32)srcAddr;

    if ((NULL == dstAddr) || (0U == srcAddr))
    {
        status =  -(Int32)1;
    }
    else
    {
        dmaPrm.destAddr = dstAddr;

        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004 Rule 11.3
         * MISRAC_WAIVER:  Typecasting srcAddr to UInt as expected in dmaPrms.
         */
        dmaPrm.srcAddr  = (Ptr)srcAddrInUInt;
        dmaPrm.length   = length;

        /* Assert in case there is an overflow */
        UTILS_assert(((srcAddrInUInt - gDDRBaseAddr) + length)
                     <= gMaxDdrBuffSize);

        status = Utils_dmaCopy1D(&gDumpSectionsDmaObj, &dmaPrm);
        UTILS_assert(status == EDMA3_DRV_SOK);

        /* Ensure that the M4 does not have a stale copy of the region
         * to which the copy is being made.
         */
        Cache_inv(dstAddr, length, Cache_Type_ALL, (Bool)TRUE);

        #if UTILS_BOOT_SLAVES_DEBUG
        Vps_printf(" UTILS: BOOT SLAVES DDR Copy: section dst [0x%x] src [0x%x] length [0x%x]",
                     dstAddr, srcAddr, length);
        #endif
    }

    return status;
}

static Int32 Utils_ddrReadMemCpy(Void   *dstAddr,
                                 UInt32  srcAddr,
                                 UInt32  length)
{
    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004 Rule 11.3
     * MISRAC_WAIVER:  Typecasting crcAddr from void * to uint
     * for checking. This check makes sure that source address + length
     * never goes out of allocated memory space in ddr.
     */
    /* Assert in case there is an overflow */
    UTILS_assert((((UInt32)srcAddr - gDDRBaseAddr) + length)
                 <= gMaxDdrBuffSize);

    memcpy(dstAddr, (Void*) srcAddr, length);

    #if UTILS_BOOT_SLAVES_DEBUG
    Vps_printf(" UTILS: BOOT SLAVES DDR Copy: section dst [0x%x] src [0x%x] length [0x%x]",
                 dstAddr, srcAddr, length);
    #endif

    return 0;
}

static Int32 Utils_qspiReadSectorsMemCpy(Void       *dstAddr,
                                         UInt32 srcOffsetAddr,
                                         UInt32      length)
{
    /* Read from QSPI */
    QSPI_ReadSectors(dstAddr, srcOffsetAddr, length);

    #if UTILS_BOOT_SLAVES_DEBUG
    Vps_printf(" UTILS: BOOT SLAVES: section dst [0x%x] src [0x%x] length [0x%x]",
                 dstAddr, (SOC_QSPI_ADDRSP1_BASE + srcOffsetAddr), length);
    #endif

    return 0;
}

static void Utils_printFxn(const char* msg)
{
    /* Read from QSPI */
    Vps_printf(msg);
    return;
}

Int32 Utils_bootSlaves(const Utils_BootSlaves_Params *params)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    Utils_DmaChCreateParams dmaParams;
    sbllibInitParams_t sblInitPrms;
    sbllibAppImageParseParams_t uclateAppPrms;
    pmlibSysConfigPowerStateParams_t inputTableDsp1[] =
    {{PMHAL_PRCM_MOD_DSP1,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED}};
    pmlibSysConfigPowerStateParams_t inputTableDsp2[] =
    {{PMHAL_PRCM_MOD_DSP2,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED}};
    pmlibSysConfigPowerStateParams_t inputTableEve1[] =
    {{PMHAL_PRCM_MOD_EVE1,                     PMLIB_SYS_CONFIG_ALWAYS_ENABLED}};

    if (params->loadCode == (Bool)TRUE)
    {
        /* Default initialization of SBL Lib Params */
        SBLLibInitParamsInit(&sblInitPrms);

        /* Default initialization of UCLate App Params */
        SBLLibAppImageParamsInit(&uclateAppPrms);

        /* Default initialization of dma Params */
        Utils_DmaChCreateParams_Init(&dmaParams);
        /* Create DMA channel for transfer */
        status = Utils_dmaCreateCh(
                        &gDumpSectionsDmaObj,
                        &dmaParams
                        );
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
#if UTILS_BOOT_SLAVES_DEBUG
        PlatformQSPISetPinMux();
#endif
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP1))
    {
        status = PMLIBSysConfigSetPowerState(inputTableDsp1, (UInt32) 1,
                                             PM_TIMEOUT_INFINITE,
                                             NULL);
        #if UTILS_BOOT_SLAVES_DEBUG
        Vps_printf(" UTILS: BOOT SLAVES: Resetting DSP1\n");
        #endif
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP2))
    {
        status = PMLIBSysConfigSetPowerState(inputTableDsp2, (UInt32) 1,
                                             PM_TIMEOUT_INFINITE,
                                             NULL);
        #if UTILS_BOOT_SLAVES_DEBUG
        Vps_printf(" UTILS: BOOT SLAVES: Resetting DSP2\n");
        #endif

    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE1))
    {
        status = PMLIBSysConfigSetPowerState(inputTableEve1, (UInt32) 1,
                                             PM_TIMEOUT_INFINITE,
                                             NULL);
        #if UTILS_BOOT_SLAVES_DEBUG
        Vps_printf(" UTILS: BOOT SLAVES: Resetting EVE1\n");
        #endif
    }

    if (params->loadCode == (Bool)TRUE)
    {
        QSPI_Initialize(DEVICE_TYPE_QSPI4);

        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
        QSPI_ConfMAddrSpace((UInt8)QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,(qspi_ChipSelect_e)QSPI_CS0);

#if UTILS_BOOT_SLAVES_DEBUG
        Vps_printf(" UTILS: BOOT SLAVES: QSPI initialization done\n");
#endif

        /* Assign SBL Params */
        sblInitPrms.printFxn     = &Utils_printFxn;
        SBLLibInit(&sblInitPrms);

        /* Assign App Image Parse Params */
        uclateAppPrms.appImgMetaHeaderV2 = &sblAppMetaHeaderV2;
        uclateAppPrms.appImgRPRCHeader = &sblAppRPRCHeader;
        uclateAppPrms.entryPoints = &gSblLibEntryPoints;
        uclateAppPrms.appImageOffset = params->uclateOffset;
        uclateAppPrms.ddrAppImageAddress = params->ddrAddress;
        uclateAppPrms.enableCrc = (uint32_t)params->enableCrc;

        /* Assign Max Buffer Size and DDR base address */
        gMaxDdrBuffSize = params->maxDdrBuffSize;
        gDDRBaseAddr = params->ddrAddress;

        if(params->useEdma)
        {
            SBLLibRegisterImageCopyCallback(&Utils_qspiReadSectorsEdma,
                                            &Utils_ddrReadEdma,
                                            &QSPI_seek);
        }
        else
        {
            SBLLibRegisterImageCopyCallback(&Utils_qspiReadSectorsMemCpy,
                                            &Utils_ddrReadMemCpy,
                                            &QSPI_seek);
        }

        if(TRUE == uclateAppPrms.enableCrc)
        {
            SBLLibRegisterCRCCallback(&Utils_computeCRC);
        }

        status = SBLLibMultiCoreImageParseV2(&uclateAppPrms);

#if UTILS_BOOT_SLAVES_DEBUG
        Vps_printf(" UTILS: BOOT SLAVES: AppImage parsing done\n");
#endif
        Utils_dmaDeleteCh(&gDumpSectionsDmaObj);
    }
    if(status >= 0)
    {
        if(System_isProcEnabled(SYSTEM_PROC_DSP1))
        {
            /* Restore the context */
            /* MISRA.CAST.PTR_TO_INT
            * MISRAC_2004_Rule_11.3
            * Casting between a pointer to an integral type
            * KW State: Ignore -> Waiver -> Case by case
            * MISRAC_WAIVER: Address is used/accessed to local variable
            */
            if (gDsp1L2ramSaveDdrAddress != 0U)
            {
                Utils_DmaCopy1D dmaPrm;
                /* Default initialization of dma Params */
                Utils_DmaChCreateParams_Init(&dmaParams);
                /* Create DMA channel for transfer */
                status = Utils_dmaCreateCh(
                        &gDumpSectionsDmaObj,
                        &dmaParams
                        );
                dmaPrm.destAddr = (Ptr)SOC_DSP1_L2_SRAM_BASE;

                dmaPrm.srcAddr  = (Ptr)gDsp1L2ramSaveDdrAddress;
                dmaPrm.length   = UTILS_MEM_L2RAM_SIZE;

                status = Utils_dmaCopy1D(&gDumpSectionsDmaObj, &dmaPrm);
                UTILS_assert(status == EDMA3_DRV_SOK);

                Utils_dmaDeleteCh(&gDumpSectionsDmaObj);
                Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) gDsp1L2ramSaveDdrAddress, UTILS_MEM_L2RAM_SIZE);

                gDsp1L2ramSaveDdrAddress = 0U;
            }

            SBLLibDSP1BringUp(gSblLibEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP1],
                              SBLLIB_SBL_BUILD_MODE_DEV);
            #if UTILS_BOOT_SLAVES_DEBUG
            Vps_printf(" UTILS: BOOT SLAVES: DSP1 bringup done \n");
            #endif
        }
        if(System_isProcEnabled(SYSTEM_PROC_DSP2))
        {
            /* Restore the context */
        /* MISRA.CAST.PTR_TO_INT
        * MISRAC_2004_Rule_11.3
        * Casting between a pointer to an integral type
        * KW State: Ignore -> Waiver -> Case by case
        * MISRAC_WAIVER: Address is used/accessed to local variable
        */
            if (gDsp2L2ramSaveDdrAddress != 0U)
            {
                Utils_DmaCopy1D dmaPrm;
                /* Default initialization of dma Params */
                Utils_DmaChCreateParams_Init(&dmaParams);
                /* Create DMA channel for transfer */
                status = Utils_dmaCreateCh(
                        &gDumpSectionsDmaObj,
                        &dmaParams
                        );
                dmaPrm.destAddr = (Ptr)SOC_DSP2_L2_SRAM_BASE;

                dmaPrm.srcAddr  = (Ptr)gDsp2L2ramSaveDdrAddress;
                dmaPrm.length   = UTILS_MEM_L2RAM_SIZE;

                status = Utils_dmaCopy1D(&gDumpSectionsDmaObj, &dmaPrm);
                UTILS_assert(status == EDMA3_DRV_SOK);

                Utils_dmaDeleteCh(&gDumpSectionsDmaObj);
                Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, (Ptr) gDsp2L2ramSaveDdrAddress, UTILS_MEM_L2RAM_SIZE);

                gDsp2L2ramSaveDdrAddress = 0U;
            }

            SBLLibDSP2BringUp(gSblLibEntryPoints.entryPoint[SBLLIB_CORE_ID_DSP2],
                              SBLLIB_SBL_BUILD_MODE_DEV);
            #if UTILS_BOOT_SLAVES_DEBUG
            Vps_printf(" UTILS: BOOT SLAVES: DSP2 bringup done \n");
            #endif
        }
        if(System_isProcEnabled(SYSTEM_PROC_EVE1))
        {
            SBLLibEVE1BringUp(gSblLibEntryPoints.entryPoint[SBLLIB_CORE_ID_EVE1],
                              SBLLIB_SBL_BUILD_MODE_DEV);
            #if UTILS_BOOT_SLAVES_DEBUG
            Vps_printf(" UTILS: BOOT SLAVES: EVE1 bringup done \n");
            #endif
        }
    }
    return status;
}


Void Utils_syncSlaves(void)
{
    System_ipcStart();

#ifdef IPC_LIB_INCLUDE
    if(System_isProcEnabled(SYSTEM_PROC_EVE1))
    {
        System_ipcNotifyReset(SYSTEM_PROC_EVE1);
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP1))
    {
        System_ipcNotifyReset(SYSTEM_PROC_DSP1);
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP2))
    {
        System_ipcNotifyReset(SYSTEM_PROC_DSP2);
    }
#endif

    if(System_isProcEnabled(SYSTEM_PROC_DSP1))
    {
        System_coreInitDone(SYSTEM_PROC_DSP1);
        System_coreTestInitDone(SYSTEM_PROC_DSP1);
    }

    if(System_isProcEnabled(SYSTEM_PROC_DSP2))
    {
        System_coreInitDone(SYSTEM_PROC_DSP2);
        System_coreTestInitDone(SYSTEM_PROC_DSP2);
    }

    if(System_isProcEnabled(SYSTEM_PROC_EVE1))
    {
        System_coreInitDone(SYSTEM_PROC_EVE1);
        System_coreTestInitDone(SYSTEM_PROC_EVE1);
    }

    System_confirmInitDone();

    if(System_isProcEnabled(SYSTEM_PROC_DSP1))
    {
        System_setCoreState(SYSTEM_PROC_DSP1, SYSTEM_CORE_STATE_ACTIVE);
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP2))
    {
        System_setCoreState(SYSTEM_PROC_DSP2, SYSTEM_CORE_STATE_ACTIVE);
    }
    if(System_isProcEnabled(SYSTEM_PROC_EVE1))
    {
        System_setCoreState(SYSTEM_PROC_EVE1, SYSTEM_CORE_STATE_ACTIVE);
    }

}

Void Utils_bootPowerDownSlaves(Void)
{
    UInt32 state = 0U;
    pmErrCode_t status = PM_SUCCESS;
    Int32 retval = SYSTEM_LINK_STATUS_SOK;
    UInt32 cookie;
    pmlibSysConfigPowerState_t currentState;
    /* Order from EVE to DSP2 to DSP1 is maintained for the IPC detach
     * to go from larger PROC_ID to smaller PROC_ID.
     */
    if(System_isProcEnabled(SYSTEM_PROC_EVE1))
    {
        /* The Application is asked to exit on EVE1 */
        Utils_setAppInitState(SYSTEM_PROC_EVE1, CORE_APP_INITSTATUS_DO_EXIT);
        do
        {
            /* Wait for core application to exit */
            Utils_getAppInitState(SYSTEM_PROC_EVE1, &state);
            if (CORE_APP_INITSTATUS_EXIT_DONE != state)
            {
                BspOsal_sleep(1U);
            }
        } while (CORE_APP_INITSTATUS_EXIT_DONE != state);
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP2))
    {
        /* The Application is asked to exit on DSP2 */
        Utils_setAppInitState(SYSTEM_PROC_DSP2, CORE_APP_INITSTATUS_DO_EXIT);
        do
        {
            /* Wait for core application to exit */
            Utils_getAppInitState(SYSTEM_PROC_DSP2, &state);
            if (CORE_APP_INITSTATUS_EXIT_DONE != state)
            {
                BspOsal_sleep(1U);
            }
        } while (CORE_APP_INITSTATUS_EXIT_DONE != state);
    }
    if(System_isProcEnabled(SYSTEM_PROC_DSP1))
    {
        /* The Application is asked to exit on DSP1 */
        Utils_setAppInitState(SYSTEM_PROC_DSP1, CORE_APP_INITSTATUS_DO_EXIT);
        do
        {
            /* The Application is asked to exit on DSP1 */
            Utils_getAppInitState(SYSTEM_PROC_DSP1, &state);
            if (CORE_APP_INITSTATUS_EXIT_DONE != state)
            {
                BspOsal_sleep(1U);
            }
        } while (CORE_APP_INITSTATUS_EXIT_DONE != state);
    }
    cookie = Hwi_disable();
#ifndef IPC_LIB_INCLUDE
     System_ipcNotifyDeInit();
#endif
    System_ipcDetach();
    System_ipcStop();

    Hwi_restore(cookie);
    if(System_isProcEnabled(SYSTEM_PROC_DSP1))
    {

        /* Save the context */
        /* MISRA.CAST.PTR_TO_INT
        * MISRAC_2004_Rule_11.3
        * Casting between a pointer to an integral type
        * KW State: Ignore -> Waiver -> Case by case
        * MISRAC_WAIVER: Shared memory address is assigned to local variable
        */
        gDsp1L2ramSaveDdrAddress = (UInt32) Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                                  UTILS_MEM_L2RAM_SIZE,
                                                  4U);
        if (gDsp1L2ramSaveDdrAddress != 0U)
        {
            Utils_DmaCopy1D dmaPrm;
            Utils_DmaChCreateParams dmaParams;
            /* Default initialization of dma Params */
            Utils_DmaChCreateParams_Init(&dmaParams);
            /* Create DMA channel for transfer */
            retval = Utils_dmaCreateCh(
                    &gDumpSectionsDmaObj,
                    &dmaParams
                    );
            UTILS_assert(retval == EDMA3_DRV_SOK);
            /* MISRA.CAST.PTR_TO_INT
            * MISRAC_2004_Rule_11.3
            * Casting between a pointer to an integral type
            * KW State: Ignore -> Waiver -> Case by case
            * MISRAC_WAIVER: dspl2ram address is assigned to local variable
            */
            dmaPrm.destAddr = (Ptr)gDsp1L2ramSaveDdrAddress;

            dmaPrm.srcAddr  = (Ptr)SOC_DSP1_L2_SRAM_BASE;
            dmaPrm.length   = UTILS_MEM_L2RAM_SIZE;

            retval = Utils_dmaCopy1D(&gDumpSectionsDmaObj, &dmaPrm);
            UTILS_assert(retval == EDMA3_DRV_SOK);

            Utils_dmaDeleteCh(&gDumpSectionsDmaObj);
        }

        do
        {
            pmlibSysConfigPowerStateParams_t inputTableDsp1[] =
                {{PMHAL_PRCM_MOD_DSP1,        PMLIB_SYS_CONFIG_DISABLED}};
            status = PMLIBSysConfigSetPowerState(inputTableDsp1, (UInt32) 1,
                                             PM_TIMEOUT_INFINITE,
                                             NULL);
            status = PMLIBSysConfigGetPowerState(PMHAL_PRCM_MOD_DSP1, &currentState, NULL);
        } while ((PM_SUCCESS == status) && (PMLIB_SYS_CONFIG_DISABLED != currentState));
        if (PM_SUCCESS != status)
        {
           Vps_printf(" UTILS: BOOT SLAVES: Powering down DSP failed!!\n");
        }
        else
        {
            System_setCoreState(SYSTEM_PROC_DSP1, SYSTEM_CORE_STATE_POWER_DOWN);
        }
    }
    if(((Bool)TRUE == System_isProcEnabled(SYSTEM_PROC_DSP2)) &&
       (PM_SUCCESS == status))
    {
        /* Save the context */
        /* MISRA.CAST.PTR_TO_INT
        * MISRAC_2004_Rule_11.3
        * Casting between a pointer to an integral type
        * KW State: Ignore -> Waiver -> Case by case
        * MISRAC_WAIVER: Shared memory address is assigned to local variable
        */
        gDsp2L2ramSaveDdrAddress = (UInt32) Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                                  UTILS_MEM_L2RAM_SIZE,
                                                  4U);
        if (gDsp2L2ramSaveDdrAddress != 0U)
        {
            Utils_DmaCopy1D dmaPrm;
            Utils_DmaChCreateParams dmaParams;
            /* Default initialization of dma Params */
            Utils_DmaChCreateParams_Init(&dmaParams);
            /* Create DMA channel for transfer */
            retval = Utils_dmaCreateCh(
                    &gDumpSectionsDmaObj,
                    &dmaParams
                    );
            UTILS_assert(retval == EDMA3_DRV_SOK);
        /* MISRA.CAST.PTR_TO_INT
        * MISRAC_2004_Rule_11.3
        * Casting between a pointer to an integral type
        * KW State: Ignore -> Waiver -> Case by case
        * MISRAC_WAIVER: dspl2ram address is assigned to local variable
        */
            dmaPrm.destAddr = (Ptr)gDsp2L2ramSaveDdrAddress;
            dmaPrm.srcAddr  = (Ptr)SOC_DSP2_L2_SRAM_BASE;
            dmaPrm.length   = UTILS_MEM_L2RAM_SIZE;

            retval = Utils_dmaCopy1D(&gDumpSectionsDmaObj, &dmaPrm);
            UTILS_assert(retval == EDMA3_DRV_SOK);

            Utils_dmaDeleteCh(&gDumpSectionsDmaObj);
        }
        do
        {
            pmlibSysConfigPowerStateParams_t inputTableDsp2[] =
                {{PMHAL_PRCM_MOD_DSP2,        PMLIB_SYS_CONFIG_DISABLED}};
            status = PMLIBSysConfigSetPowerState(inputTableDsp2, (UInt32) 1,
                                             PM_TIMEOUT_INFINITE,
                                             NULL);
            status = PMLIBSysConfigGetPowerState(PMHAL_PRCM_MOD_DSP2, &currentState, NULL);
        } while ((PM_SUCCESS == status) && (PMLIB_SYS_CONFIG_DISABLED != currentState));
        if (PM_SUCCESS != status)
        {
           Vps_printf(" UTILS: BOOT SLAVES: Powering down DSP failed!!\n");
        }
        else
        {
            System_setCoreState(SYSTEM_PROC_DSP2, SYSTEM_CORE_STATE_POWER_DOWN);
        }

    }
    if(((Bool)TRUE == System_isProcEnabled(SYSTEM_PROC_EVE1)) &&
       (PM_SUCCESS == status))
    {
        do
        {
            pmlibSysConfigPowerStateParams_t inputTableEve1[] =
                {{PMHAL_PRCM_MOD_EVE1,    PMLIB_SYS_CONFIG_DISABLED}};
            status = PMLIBSysConfigSetPowerState(inputTableEve1, (UInt32) 1,
                                             PM_TIMEOUT_INFINITE,
                                             NULL);
            status = PMLIBSysConfigGetPowerState(PMHAL_PRCM_MOD_EVE1, &currentState, NULL);
        } while ((PM_SUCCESS == status) && (PMLIB_SYS_CONFIG_DISABLED != currentState));
        if (PM_SUCCESS != status)
        {
           Vps_printf(" UTILS: BOOT SLAVES: Powering down EVE failed!!\n");
        }
        else
        {
            System_setCoreState(SYSTEM_PROC_EVE1, SYSTEM_CORE_STATE_POWER_DOWN);
        }

    }
    if (PM_SUCCESS == status)
    {
        Vps_printf(" UTILS: BOOT SLAVES: Powering Down Successful!!\n");
    }
    else
    {
        Vps_printf(" UTILS: BOOT SLAVES: Powering Down NOT Successful!!\n");
    }
}

/* Nothing past this point */
