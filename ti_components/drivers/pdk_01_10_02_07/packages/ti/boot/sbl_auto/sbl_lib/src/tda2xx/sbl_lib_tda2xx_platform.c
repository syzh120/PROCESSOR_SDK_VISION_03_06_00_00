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
 *  \file     sbl_lib_tda2xx_platform.c
 *
 *  \brief    This file contains the SBL Library layer for TDA2xx SOC family.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#if defined (__ARM_ARCH_7A__)
#include <ti/csl/arch/csl_arch.h>
#endif
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <sbl_lib_tda2xx_priv.h>
#include <ti/csl/csl_mmu.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmlib.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Define DSP1's boot address value when entry point is zero */
#define SBL_LIB_DSP1_BOOT_ADDRESS_VAL      (SBLLIB_SOC_DSP_L2_BASE)

/* Define DSP2's boot address value when entry point is zero */
#define SBL_LIB_DSP2_BOOT_ADDRESS_VAL      (SBLLIB_SOC_DSP_L2_BASE)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
/**
 * \brief   This function configures the EVE MMU as per EVE's entry point.
 *          Contains entries to access entry location page, L4 peripheral
 *          space and internal memories. Remaining DDR entries should be
 *          taken care by application.
 *
 * \param   baseAddr       Base address of EVE MMU.
 * \param   entryPoint     Entry Point of EVE.
 *
 * \retVal  None.
 */
static void SblLibEVEMMUConfig(uint32_t baseAddr, uint32_t entryPoint);

#if defined (__ARM_ARCH_7A__)
/**
 * \brief   This API Cleans Invalidates and evicts data cache. This function is
 *          defined in cp15.h but SBL Library cannot have sys_config dependency
 *          Hence this API is defined again in SBL Library.
 *
 * \param   None.
 *
 * \retVal  None.
 */
static void SblLibCP15DCacheCleanFlush(void);

/**
 * \brief   This function sends the event instruction i.e. SEV.
 *
 * \param   None.
 *
 * \retval  None.
 */
static void SblLibSendEvent(void);
#endif
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Global variable for referencing the Boot Media App Image Read function */
static SBLLibMediaReadFxn gMediaReadFxn = NULL;

/* Global variable for referencing the DDR App Image Read function */
static SBLLibDDRReadFxn   gDDRReadFxn = NULL;

/*
 * Global variable for referencing the location upto which App Image has been
 * read
 */
static SBLLibSeekFxn      gSeekFxn = NULL;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SBLLibAppImageParamsInit(sbllibAppImageParseParams_t *imageParams)
{
    imageParams->appImgMetaHeaderV1 = NULL;
    imageParams->appImgMetaHeaderV2 = NULL;
    imageParams->appImgRPRCHeader   = NULL;
    imageParams->entryPoints        = NULL;
    imageParams->appImageOffset     = 0U;
    imageParams->ddrAppImageAddress = 0U;
    imageParams->skipDDRCopy        = 0U;
    imageParams->enableCrc          = (uint32_t) FALSE;
}

int32_t SBLLibMultiCoreImageParseV1(sbllibAppImageParseParams_t *imageParams)
{
    uint32_t fileNo, entryPoint = 0U, address;
    uint32_t magicStr         = SBLLIB_META_HEADER_MAGIC_STR;
    uint32_t currAppImageAddr = imageParams->appImageOffset;
    uint32_t rprcImageSize    = 0U;
    int32_t  retVal           = STW_SOK;

    if ((0U == imageParams->ddrAppImageAddress) &&
        (0U == imageParams->skipDDRCopy))
    {
        retVal = STW_EFAIL;
    }
    else if ((NULL == gMediaReadFxn) ||
             (NULL == gDDRReadFxn) ||
             (NULL == gSeekFxn) ||
             (NULL == imageParams->appImgMetaHeaderV1) ||
             (NULL == imageParams->appImgRPRCHeader) ||
             (NULL == imageParams->entryPoints))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Make sure the read head points to start of App Image */
        gSeekFxn(&currAppImageAddr, imageParams->appImageOffset);

        /* Read meta header start and get the number of RPRC Images */
        gMediaReadFxn(&imageParams->appImgMetaHeaderV1->metaHeaderStartV1,
                      currAppImageAddr,
                      sizeof (sbllibMetaHeaderStartV1_t));
        currAppImageAddr += sizeof (sbllibMetaHeaderStartV1_t);

        if ((uint32_t) magicStr !=
            imageParams->appImgMetaHeaderV1->metaHeaderStartV1.magicStr)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\nInvalid Magic String in MultiCore Image\r\n");
            retVal = STW_EFAIL;
        }
        else
        {
            if (imageParams->appImgMetaHeaderV1->metaHeaderStartV1.devId !=
                SBLLibGetDeviceId())
            {
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                             "\nWARNING: Device Id Does not Match\r\n");
            }

            /* Read all the core offset addresses */
            for (fileNo = 0U;
                 fileNo <
                 imageParams->appImgMetaHeaderV1->metaHeaderStartV1.numFiles;
                 fileNo++)
            {
                gMediaReadFxn(
                    &imageParams->appImgMetaHeaderV1->metaHeaderCoreV1[fileNo],
                    currAppImageAddr,
                    sizeof (sbllibMetaHeaderCoreV1_t));
                currAppImageAddr += sizeof (sbllibMetaHeaderCoreV1_t);
            }

            /* Read meta header end */
            gMediaReadFxn(&imageParams->appImgMetaHeaderV1->metaHeaderEnd,
                          currAppImageAddr,
                          sizeof (sbllibMetaHeaderEnd_t));
            currAppImageAddr += sizeof (sbllibMetaHeaderEnd_t);

            /* Add base offset address with core image start offset for all
             * cores
             */
            for (fileNo = 0U;
                 fileNo <
                 imageParams->appImgMetaHeaderV1->metaHeaderStartV1.numFiles;
                 fileNo++)
            {
                imageParams->appImgMetaHeaderV1->
                metaHeaderCoreV1[fileNo].imageOffset +=
                    imageParams->appImageOffset;
            }

            /* Now parse individual RPRC files */
            for (fileNo = 0U;
                 fileNo <
                 imageParams->appImgMetaHeaderV1->metaHeaderStartV1.numFiles;
                 fileNo++)
            {
                if (((uint32_t) 0xFFFFFFFFU) !=
                    imageParams->appImgMetaHeaderV1->
                    metaHeaderCoreV1[fileNo].coreId)
                {
                    gSeekFxn(&currAppImageAddr,
                             imageParams->appImgMetaHeaderV1->
                             metaHeaderCoreV1[fileNo].imageOffset);

                    rprcImageSize =
                        SBLLibCalculateRprcImageSize(
                            imageParams->appImgRPRCHeader,
                            imageParams->appImgMetaHeaderV1->metaHeaderCoreV1[
                                fileNo].imageOffset);

                    /* Make sure the read head points to RPRC Header */
                    gSeekFxn(&currAppImageAddr,
                             imageParams->appImgMetaHeaderV1->
                             metaHeaderCoreV1[fileNo].imageOffset);

                    if (0U == imageParams->skipDDRCopy)
                    {
                        gMediaReadFxn(
                            (void *) imageParams->ddrAppImageAddress,
                            currAppImageAddr,
                            rprcImageSize);
                    }

                    if (0U == imageParams->skipDDRCopy)
                    {
                        address = imageParams->ddrAppImageAddress;
                    }
                    else
                    {
                        address = currAppImageAddr;
                    }

                    if (STW_SOK !=
                        SBLLibRprcImageParse(imageParams->appImgRPRCHeader,
                                             (void *) address,
                                             &entryPoint,
                                             imageParams->
                                             appImgMetaHeaderV1->
                                             metaHeaderCoreV1[fileNo].
                                             coreId,
                                             imageParams->skipDDRCopy))
                    {
                        /* Error occurred parsing the RPRC file. Continue
                         * parsing the next
                         * image and skip booting the particular core.
                         */
                        retVal = STW_EFAIL;
                    }
                    else
                    {
                        SBLLibBootCore(
                            entryPoint,
                            imageParams->appImgMetaHeaderV1->
                            metaHeaderCoreV1[fileNo].coreId,
                            imageParams->entryPoints);
                    }
                }
            }
        }
    }
    return retVal;
}

int32_t SBLLibMultiCoreImageParseV2(sbllibAppImageParseParams_t *imageParams)
{
    uint32_t fileNo, entryPoint = 0U, address;
    uint32_t magicStrHdrStart = SBLLIB_META_HEADER_MAGIC_STR;
    uint32_t magicStrHdrEnd   = SBLLIB_META_HEADER_MAGIC_END;
    uint32_t currAppImageAddr = imageParams->appImageOffset;
    int32_t  retVal           = STW_SOK;
    uint32_t size;

    if ((0U == imageParams->ddrAppImageAddress) &&
        (0U == imageParams->skipDDRCopy))
    {
        retVal = STW_EFAIL;
    }
    else if ((NULL == gMediaReadFxn) ||
             (NULL == gDDRReadFxn) ||
             (NULL == gSeekFxn) ||
             (NULL == imageParams->appImgMetaHeaderV2) ||
             (NULL == imageParams->appImgRPRCHeader) ||
             (NULL == imageParams->entryPoints))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Read meta header start and get the number of RPRC Images */
        gMediaReadFxn(&imageParams->appImgMetaHeaderV2->metaHeaderStartV2,
                      currAppImageAddr,
                      sizeof (sbllibMetaHeaderStartV2_t));
        currAppImageAddr += sizeof (sbllibMetaHeaderStartV2_t);

        if ((uint32_t) magicStrHdrStart !=
            imageParams->appImgMetaHeaderV2->metaHeaderStartV2.magicStr)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\nInvalid Magic String in MultiCore Image\r\n");
            retVal = STW_EFAIL;
        }
        else
        {
            if (imageParams->appImgMetaHeaderV2->metaHeaderStartV2.devId !=
                SBLLibGetDeviceId())
            {
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                             "\nWARNING: Device Id Does not Match\r\n");
            }

            /* Read all the core offset addresses */
            for (fileNo = 0U;
                 fileNo <
                 imageParams->appImgMetaHeaderV2->metaHeaderStartV2.numFiles;
                 fileNo++)
            {
                gMediaReadFxn(
                    &imageParams->appImgMetaHeaderV2->metaHeaderCoreV2[fileNo],
                    currAppImageAddr,
                    sizeof (sbllibMetaHeaderCoreV2_t));
                currAppImageAddr += sizeof (sbllibMetaHeaderCoreV2_t);
            }

            /* Read meta header end */
            gMediaReadFxn(&imageParams->appImgMetaHeaderV2->metaHeaderEnd,
                          currAppImageAddr,
                          sizeof (sbllibMetaHeaderEnd_t));
            currAppImageAddr += sizeof (sbllibMetaHeaderEnd_t);

            if ((uint32_t) magicStrHdrEnd !=
                imageParams->appImgMetaHeaderV2->metaHeaderEnd.magicStringEnd)
            {
                if ((uint32_t) TRUE == SblLibIsExecutingOnA15HS())
                {
                    SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                 "\n Un-authenticated image \n");
                    SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                 "\n Aborting Boot \n");
                    SBLLibAbortBoot();
                }
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_IMP_INFO,
                    "\nTrying to boot App Image with header version 1\r\n");
                SBLLibMultiCoreImageParseV1(imageParams);
            }
            else
            {
                /* Add base offset address with core image start offset for all
                 * cores
                 */
                for (fileNo = 0U;
                     fileNo <
                     imageParams->appImgMetaHeaderV2->metaHeaderStartV2.
                     numFiles;
                     fileNo++)
                {
                    imageParams->appImgMetaHeaderV2->
                    metaHeaderCoreV2[fileNo].imageOffset +=
                        imageParams->appImageOffset;
                }

                /* Now parse individual RPRC files */
                for (fileNo = 0U;
                     fileNo <
                     imageParams->appImgMetaHeaderV2->metaHeaderStartV2.
                     numFiles;
                     fileNo++)
                {
                    if ((1U == imageParams->appImgMetaHeaderV2->
                         metaHeaderCoreV2[fileNo].isRprcImageValid) &&
                        (((uint32_t) 0xFFFFFFFFU) !=
                         imageParams->appImgMetaHeaderV2->
                         metaHeaderCoreV2[fileNo].coreId))
                    {
                        gSeekFxn(&currAppImageAddr,
                                 imageParams->appImgMetaHeaderV2->
                                 metaHeaderCoreV2[fileNo].imageOffset);

                        if (0U == imageParams->skipDDRCopy)
                        {
                            gMediaReadFxn(
                                (void *) imageParams->ddrAppImageAddress,
                                currAppImageAddr,
                                imageParams->appImgMetaHeaderV2->
                                metaHeaderCoreV2[fileNo].rprcImageSize);
                        }

                        /* Authenticate RPRC images on HS devices
                         * Authentication function will always return STW_SOK
                         * on TDA2x GP devices
                         */
                        if (0U == imageParams->skipDDRCopy)
                        {
                            address = imageParams->ddrAppImageAddress;
                        }
                        else
                        {
                            address = currAppImageAddr;
                        }
                        size = imageParams->appImgMetaHeaderV2->
                               metaHeaderCoreV2[fileNo].rprcImageSize;
                        retVal = SBLLibHSAuthenticateBinary(address, size);
                        if (STW_SOK != retVal)
                        {
                            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                         "\n Un-authenticated image \n");
                            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                         "\n Aborting Boot \n");
                            SBLLibAbortBoot();
                        }

                        if (STW_SOK !=
                            SBLLibRprcImageParse(imageParams->appImgRPRCHeader,
                                                 (void *) address,
                                                 &entryPoint,
                                                 imageParams->
                                                 appImgMetaHeaderV2->
                                                 metaHeaderCoreV2[fileNo].
                                                 coreId,
                                                 imageParams->skipDDRCopy))
                        {
                            /* Error occurred parsing the RPRC file. Continue
                             * parsing the next
                             * image and skip booting the particular core.
                             */
                            retVal = STW_EFAIL;
                        }
                        else
                        {
                            SBLLibBootCore(
                                entryPoint,
                                imageParams->appImgMetaHeaderV2->
                                metaHeaderCoreV2[fileNo].coreId,
                                imageParams->entryPoints);
                        }
                    }
                }
            }
        }
    }
    return retVal;
}

uint32_t SBLLibCalculateRprcImageSize(sbllibRPRCImageHeader_t *rprcHeader,
                                      uint32_t                 rprcImageAddr)
{
    uint32_t rprcImageSize     = 0U, numSections = 0U;
    uint32_t currRprcImageAddr = rprcImageAddr;

    /* Read RPRC image header */
    gMediaReadFxn(&rprcHeader->rprcFileHeader,
                  currRprcImageAddr,
                  sizeof (sbllibRprcFileHeader_t));
    currRprcImageAddr += sizeof (sbllibRprcFileHeader_t);

    /* Read each section header to find section size */
    for (numSections = 0;
         numSections < rprcHeader->rprcFileHeader.sectionCount;
         numSections++)
    {
        /* Read new section header */
        gMediaReadFxn(
            &rprcHeader->rprcSectionHeader,
            currRprcImageAddr,
            sizeof (sbllibRprcSectionHeader_t));
        currRprcImageAddr += sizeof (sbllibRprcSectionHeader_t);

        currRprcImageAddr += rprcHeader->rprcSectionHeader.sectionSize;
    }

    rprcImageSize = currRprcImageAddr - rprcImageAddr;

    return rprcImageSize;
}

int32_t SBLLibRprcImageParse(sbllibRPRCImageHeader_t *rprcHeader,
                             const void              *rprcImageAddr,
                             uint32_t                *entryPoint,
                             uint32_t                 coreId,
                             uint32_t                 isImageInDDR)
{
    uint32_t           numSections;
    int32_t            retVal            = STW_SOK;
    uint32_t           rprcTransferSize  = 0U;
    uint32_t           currRprcImageAddr = (uint32_t) rprcImageAddr;

    SBLLibMediaReadFxn readFxn = NULL;

    /* Avoid redundant copy if image is already in DDR */
    if (1U == isImageInDDR)
    {
        readFxn = gMediaReadFxn;
    }
    else
    {
        readFxn = gDDRReadFxn;
    }

    if ((NULL == rprcHeader) || (NULL == readFxn))
    {
        retVal = STW_EFAIL;
    }
    else
    {
        /* Read RPRC image header */
        readFxn(&rprcHeader->rprcFileHeader,
                currRprcImageAddr,
                sizeof (sbllibRprcFileHeader_t));
        currRprcImageAddr += sizeof (sbllibRprcFileHeader_t);

        /* Check magic string */
        if (SBLLIB_RPRC_MAGIC_STRING != rprcHeader->rprcFileHeader.magicStr)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "Invalid Magic String in Boot Image\r\n");
            retVal = STW_EFAIL;
        }
        else
        {
            /* Set the entry point */
            *entryPoint = rprcHeader->rprcFileHeader.entryPoint;

            /* Read entrypoint and copy sections to memory */
            for (numSections = 0;
                 numSections < rprcHeader->rprcFileHeader.sectionCount;
                 numSections++)
            {
                /* Read new section header */
                readFxn(
                    &rprcHeader->rprcSectionHeader,
                    currRprcImageAddr,
                    sizeof (sbllibRprcSectionHeader_t));
                currRprcImageAddr += sizeof (sbllibRprcSectionHeader_t);

                rprcTransferSize = rprcHeader->rprcSectionHeader.sectionSize;

                /* Copy section to memory */
                /* Check for section mapped into CPU internal memories */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
                if (((rprcHeader->rprcSectionHeader.loadAddr >=
                      SOC_OCMC_RAM1_BASE) &&
                     (rprcHeader->rprcSectionHeader.loadAddr <
                      (SOC_OCMC_RAM1_BASE + SBLLIB_SOC_OCMC_RAM1_SIZE))) ||
                    ((rprcHeader->rprcSectionHeader.loadAddr >=
                      SOC_OCMC_RAM2_BASE) &&
                     (rprcHeader->rprcSectionHeader.loadAddr <
                      (SOC_OCMC_RAM2_BASE + SBLLIB_SOC_OCMC_RAM2_SIZE))) ||
                    ((rprcHeader->rprcSectionHeader.loadAddr >=
                      SOC_OCMC_RAM3_BASE) &&
                     (rprcHeader->rprcSectionHeader.loadAddr <
                      (SOC_OCMC_RAM3_BASE + SBLLIB_SOC_OCMC_RAM3_SIZE))))
#elif defined (SOC_TDA2EX)
                if ((rprcHeader->rprcSectionHeader.loadAddr >=
                     SOC_OCMC_RAM1_BASE) &&
                    (rprcHeader->rprcSectionHeader.loadAddr <
                     (SOC_OCMC_RAM1_BASE + SBLLIB_SOC_OCMC_RAM1_SIZE)))
#endif
                {
                    /* Internal OCMC RAM Space for all the cores */
                }
                else if (rprcHeader->rprcSectionHeader.loadAddr < 0x80000000U)
                {
                    switch (coreId)
                    {
                        case SBLLIB_CORE_ID_MPU_CPU0:
                            /* No action */
                            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
                        case SBLLIB_CORE_ID_MPU_CPU1:
                            /* No action */
                            break;

                        case SBLLIB_CORE_ID_MPU:
                            /* No action */
                            break;
#endif
                        case SBLLIB_CORE_ID_IPU1_CPU0:
                        case SBLLIB_CORE_ID_IPU1_CPU1:
                        case SBLLIB_CORE_ID_IPU1:
                            if (rprcHeader->rprcSectionHeader.loadAddr <
                                0x10000U)
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_IPU1_RAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "IPU1 - Invalid Memory section");
                            }
                            break;

                        case SBLLIB_CORE_ID_IPU2_CPU0:
                        case SBLLIB_CORE_ID_IPU2_CPU1:
                        case SBLLIB_CORE_ID_IPU2:
                            if (rprcHeader->rprcSectionHeader.loadAddr <
                                0x10000U)
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_IPU2_RAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "IPU2 - Invalid Memory section");
                            }
                            break;

                        case SBLLIB_CORE_ID_DSP1:
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_DSP_L2_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_DSP_L2_BASE + 0x48000U)))
                            {
                                /* L2 RAM: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L2_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP1_L2_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                                #if (SBL_LIB_CONFIG_DSP1_PARITY_CHECK == 1U)
                                /* Make sure section size is 16 byte aligned */
                                rprcTransferSize +=
                                    (0x10U -
                                     (rprcHeader->rprcSectionHeader.sectionSize
                                      & 0xFU));
                                #endif
                            }
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_DSP_L1P_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_DSP_L1P_BASE + 0x8000U)))
                            {
                                /* SOC_DSP1_L1P_SRAM_BASE: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L1P_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP1_L1P_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_DSP_L1D_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_DSP_L1D_BASE + 0x8000U)))
                            {
                                /* SOC_DSP1_L1D_SRAM_BASE: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L1D_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP1_L1D_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "DSP1 - Invalid Memory section");
                            }
                            break;
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
                        case SBLLIB_CORE_ID_DSP2:
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_DSP_L2_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_DSP_L2_BASE + 0x48000U)))
                            {
                                /* L2 RAM: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L2_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP2_L2_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                                #if (SBL_LIB_CONFIG_DSP2_PARITY_CHECK == 1U)
                                /* Make sure section size is 16 byte aligned */
                                rprcTransferSize +=
                                    (0x10U -
                                     (rprcHeader->rprcSectionHeader.sectionSize
                                      & 0xFU));
                                #endif
                            }
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_DSP_L1P_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_DSP_L1P_BASE + 0x8000U)))
                            {
                                /* SOC_DSP2_L1P_SRAM_BASE: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L1P_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP2_L1P_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_DSP_L1D_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_DSP_L1D_BASE + 0x8000U)))
                            {
                                /* SOC_DSP2_L1D_SRAM_BASE: Read the offset */
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_DSP_L1D_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SOC_DSP2_L1D_SRAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "DSP2 - Invalid Memory section");
                            }
                            break;

                        case SBLLIB_CORE_ID_EVE1:
                            /*DMEM*/
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_EVE_DMEM_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_EVE_DMEM_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_DMEM_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE1_DMEM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*WMEM*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_WBUF_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_WBUF_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_WBUF_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE1_WBUF_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLA*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE1_IBUF_LA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLH*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE1_IBUF_HA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE1_IBUF_LB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFHB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE1_IBUF_HB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "EVE1 - Invalid Memory section");
                            }
                            break;

                        case SBLLIB_CORE_ID_EVE2:
                            /*DMEM*/
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_EVE_DMEM_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_EVE_DMEM_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_DMEM_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE2_DMEM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*WMEM*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_WBUF_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_WBUF_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_WBUF_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE2_WBUF_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLA*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE2_IBUF_LA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLH*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE2_IBUF_HA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE2_IBUF_LB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFHB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE2_IBUF_HB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "EVE2 - Invalid Memory section");
                            }
                            break;
#endif
#if defined (SOC_TDA2XX)
                        case SBLLIB_CORE_ID_EVE3:
                            /*DMEM*/
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_EVE_DMEM_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_EVE_DMEM_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_DMEM_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE3_DMEM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*WMEM*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_WBUF_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_WBUF_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_WBUF_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE3_WBUF_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLA*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE3_IBUF_LA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLH*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE3_IBUF_HA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE3_IBUF_LB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFHB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE3_IBUF_HB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "EVE3 - Invalid Memory section");
                            }
                            break;

                        case SBLLIB_CORE_ID_EVE4:
                            /*DMEM*/
                            if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                 SBLLIB_SOC_EVE_DMEM_BASE) &&
                                (rprcHeader->rprcSectionHeader.loadAddr <
                                 (SBLLIB_SOC_EVE_DMEM_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_DMEM_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE4_DMEM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*WMEM*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_WBUF_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_WBUF_BASE + 0x8000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_WBUF_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE4_WBUF_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLA*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE4_IBUF_LA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLH*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HA_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HA_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HA_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE4_IBUF_HA_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFLB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_LB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_LB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_LB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE4_IBUF_LB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            /*IBUFHB*/
                            else if ((rprcHeader->rprcSectionHeader.loadAddr >=
                                      SBLLIB_SOC_EVE_IBUF_HB_BASE) &&
                                     (rprcHeader->rprcSectionHeader.loadAddr <
                                      (SBLLIB_SOC_EVE_IBUF_HB_BASE + 0x4000U)))
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    rprcHeader->rprcSectionHeader.loadAddr -
                                    SBLLIB_SOC_EVE_IBUF_HB_BASE;
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_EVE4_IBUF_HB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "EVE4 - Invalid Memory section");
                            }
                            break;
#endif
                        default:
                            /* To remove MISRA C error */
                            break;
                    }
                }
                else
                {
                    /* To remove MISRA C error */
                }
                readFxn(
                    (void *) rprcHeader->rprcSectionHeader.loadAddr,
                    currRprcImageAddr,
                    rprcTransferSize);
                currRprcImageAddr += rprcHeader->rprcSectionHeader.sectionSize;
            }
        }
    }
    return retVal;
}

int32_t SBLLibGetDeviceId(void)
{
    int32_t deviceId = 0;

#if defined (SOC_TDA2XX)
    deviceId = 55;
#elif defined (SOC_TDA2EX)
    deviceId = 66;
#elif defined (SOC_TDA2PX)
    deviceId = 88;
#endif

    return deviceId;
}

int32_t SBLLibBootCore(uint32_t             entryPoint,
                       uint32_t             coreId,
                       sbllibEntryPoints_t *entryPoints)
{
    int32_t retVal = STW_SOK;

    switch (coreId)
    {
        case SBLLIB_CORE_ID_MPU_CPU0:
            /* MPU CPU0 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n MPU CPU0 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_MPU_CPU0] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_IPU1_CPU0:
            /* IPU1 CPU0 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU1 CPU0 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU0] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_IPU1_CPU1:
            /* IPU1 CPU1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU1 CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU1] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_IPU2_CPU0:
            /* IPU2 CPU0 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU2 CPU0 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU2_CPU0] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_IPU2_CPU1:
            /* IPU2 CPU1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU2 CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU2_CPU1] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_DSP1:
            /* DSP1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n DSP1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_DSP1] = entryPoint;
            break;

        case SBLLIB_CORE_ID_IPU1:
            /* IPU1 SMP */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU1 CPU0 and CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU0] =
                entryPoint;
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU1] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_IPU2:
            /* IPU2 SMP */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU2 CPU0 and CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU2_CPU0] =
                entryPoint;
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU2_CPU1] =
                entryPoint;
            break;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
        case SBLLIB_CORE_ID_MPU_CPU1:
            /* MPU CPU1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n MPU CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_MPU_CPU1] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_MPU:
            /* MPU SMP */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n MPU CPU0 and CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_MPU_CPU0] =
                entryPoint;
            entryPoints->entryPoint[SBLLIB_CORE_ID_MPU_CPU1] =
                entryPoint;
            break;

        case SBLLIB_CORE_ID_DSP2:
            /* DSP2 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n DSP2 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_DSP2] = entryPoint;
            break;

        case SBLLIB_CORE_ID_EVE1:
            /* EVE1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n EVE1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_EVE1] = entryPoint;
            break;

        case SBLLIB_CORE_ID_EVE2:
            /* EVE2 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n EVE2 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_EVE2] = entryPoint;
            break;
#endif
#if defined (SOC_TDA2XX)
        case SBLLIB_CORE_ID_EVE3:
            /* EVE3 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n EVE3 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_EVE3] = entryPoint;
            break;

        case SBLLIB_CORE_ID_EVE4:
            /* EVE4 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n EVE4 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_EVE4] = entryPoint;
            break;
#endif

        default:
            retVal = STW_EFAIL;
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Wrong Core Id: Cannot Assign entry point \n");
            break;
    }
    return retVal;
}

void SBLLibResetAllSlaveCores(void)
{
    /* Reset IPU1 sub-system */
    SBLLibIPU1SubsystemReset();

    /* Reset IPU2 sub-system */
    SBLLibIPU2SubsystemReset();

    /* Reset DSP1 */
    SBLLibCPUReset(SBLLIB_CORE_ID_DSP1);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
    /* Reset DSP2 */
    SBLLibCPUReset(SBLLIB_CORE_ID_DSP2);

    /* Reset EVE1 */
    SBLLibCPUReset(SBLLIB_CORE_ID_EVE1);

    /* Reset EVE2 */
    SBLLibCPUReset(SBLLIB_CORE_ID_EVE2);
#endif
#if defined (SOC_TDA2XX)
    /* Reset EVE3 */
    SBLLibCPUReset(SBLLIB_CORE_ID_EVE3);

    /* Reset EVE4 */
    SBLLibCPUReset(SBLLIB_CORE_ID_EVE4);
#endif
}

int32_t SBLLibIPU1SubsystemReset(void)
{
    int32_t  retVal    = STW_SOK;
    uint32_t rstStatus = 0U;

    /* Select CORE_IPU_ISS_BOOST_CLK from CORE_DPLL for IPU1_GFCLK */
    retVal = PMHALCMMuxParentSelect(PMHAL_PRCM_MUX_IPU1_GFCLK_MUX,
                                    PMHAL_PRCM_DPLL_CORE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n IPU1 Clock Selection Failed \n");
    }
    else
    {
        /* Enable IPU1 module */
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                                    PMHAL_PRCM_MODULE_MODE_AUTO,
                                    PM_TIMEOUT_INFINITE);

        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Failed to enable module IPU1 \n");
        }
        else
        {
            /* Enable IPU1 clock domain */
            retVal = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU1,
                                           PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                           PM_TIMEOUT_INFINITE);
            if (STW_SOK != retVal)
            {
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                             "\n Failed to enable clock domain IPU1 \n");
            }
        }
    }

    /* Assert the IPU1 sub-system (CPU0, CPU1 and then sub-system) reset */
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU0_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU1 CPU0 reset \n");
    }

    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU1 CPU1 reset \n");
    }

    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU1 system reset \n");
    }

    /* Check the reset status and clear */
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_CPU0_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU1 CPU0 reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_CPU0_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to clear IPU1 CPU0 reset status \n");
        }
    }

    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_CPU1_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU1 CPU1 reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_CPU1_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to clear IPU1 CPU1 reset status \n");
        }
    }

    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU1 sub-system reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Failed to clear IPU1 sub-system reset status \n");
        }
    }

    /* Configure boot translation page of IPU to IPU RAM */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR, 0x00000);
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR, 0x55020);

    /* Bring the IPU1 sub-system out of reset*/
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU1_RST, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release IPU1 sub-system reset \n");
    }

    return retVal;
}

int32_t SBLLibIPU2SubsystemReset(void)
{
    int32_t  retVal    = STW_SOK;
    uint32_t rstStatus = 0U;

    /* Enable IPU2 module */
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU2,
                                PMHAL_PRCM_MODULE_MODE_AUTO,
                                PM_TIMEOUT_INFINITE);

    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to enable module IPU2 \n");
    }
    else
    {
        /* Enable IPU2 clock domain */
        retVal = PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU2,
                                       PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP,
                                       PM_TIMEOUT_INFINITE);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Failed to enable clock domain IPU2 \n");
        }
    }

    /* Assert the IPU2 sub-system (CPU0, CPU1 and then sub-system) reset */
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_CPU0_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU2 CPU0 reset \n");
    }

    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_CPU1_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU2 CPU1 reset \n");
    }

    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU2 system reset \n");
    }

    /* Check the reset status and clear */
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_CPU0_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU2 CPU0 reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_CPU0_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to clear IPU2 CPU0 reset status \n");
        }
    }

    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_CPU1_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU2 CPU1 reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_CPU1_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to clear IPU2 CPU1 reset status \n");
        }
    }

    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU2 sub-system reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Failed to clear IPU2 sub-system reset status \n");
        }
    }

    /* Configure boot translation page of IPU to IPU RAM */
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR, 0x00000);
    HW_WR_REG32(
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR, 0x55020);

    /* Bring the IPU sub-system out of reset*/
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU2_RST, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release IPU2 sub-system reset \n");
    }

    return retVal;
}

void SBLLibCPUReset(uint32_t cpuId)
{
    pmhalPrcmResetGroupId_t systemReset = PMHAL_PRCM_RG_LOWER_BOUND;
    pmhalPrcmResetGroupId_t localReset  = PMHAL_PRCM_RG_LOWER_BOUND;
    int32_t  retVal    = STW_SOK;

    switch (cpuId)
    {
        case SBLLIB_CORE_ID_DSP1:
            systemReset = PMHAL_PRCM_RG_DSP1_SYS_RST;
            localReset  = PMHAL_PRCM_RG_DSP1_RST;
            break;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
        case SBLLIB_CORE_ID_DSP2:
            systemReset = PMHAL_PRCM_RG_DSP2_SYS_RST;
            localReset  = PMHAL_PRCM_RG_DSP2_RST;
            break;

        case SBLLIB_CORE_ID_EVE1:
            systemReset = PMHAL_PRCM_RG_EVE1_RST;
            localReset  = PMHAL_PRCM_RG_EVE1_CPU_RST;
            break;

        case SBLLIB_CORE_ID_EVE2:
            systemReset = PMHAL_PRCM_RG_EVE2_RST;
            localReset  = PMHAL_PRCM_RG_EVE2_CPU_RST;
            break;
#endif
#if defined (SOC_TDA2XX)
        case SBLLIB_CORE_ID_EVE3:
            systemReset = PMHAL_PRCM_RG_EVE3_RST;
            localReset  = PMHAL_PRCM_RG_EVE3_CPU_RST;
            break;

        case SBLLIB_CORE_ID_EVE4:
            systemReset = PMHAL_PRCM_RG_EVE4_RST;
            localReset  = PMHAL_PRCM_RG_EVE4_CPU_RST;
            break;
#endif
        default:
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                         "\n Tried to reset Wrong Slave Core \n");
            break;
    }

    /* Clear the reset status */
    retVal = PMHALResetClearStatus(localReset);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to clear Local Reset Status \n");
    }

    retVal = PMHALResetClearStatus(systemReset);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to clear System Reset status \n");
    }

    /* Assert the reset */
    retVal = PMHALResetAssert(localReset);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert Local Reset \n");
    }

    /* Assert the reset */
    retVal = PMHALResetAssert(systemReset);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert System Reset \n");
    }

    /* Clear reset for MMU, Cache and Slave interface OCP port */
    retVal = PMHALResetRelease(systemReset, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release System Reset \n");
    }
}

int32_t SBLLibRegisterImageCopyCallback(SBLLibMediaReadFxn mediaReadFxn,
                                        SBLLibDDRReadFxn   ddrReadFxn,
                                        SBLLibSeekFxn      seekFxn)
{
    int32_t retVal = STW_SOK;
    if ((mediaReadFxn != NULL) && (ddrReadFxn != NULL) && (seekFxn != NULL))
    {
        gMediaReadFxn = mediaReadFxn;
        gDDRReadFxn   = ddrReadFxn;
        gSeekFxn      = seekFxn;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

void SBLLibIPU1CPU0BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    int32_t  retVal    = 0;
    uint32_t rstStatus = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;

    /* Assert the IPU1 CPU0 reset */
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU0_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU1 CPU0 reset \n");
    }

    /* Check the reset status and clear */
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_CPU0_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU1 CPU0 reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_CPU0_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to clear IPU1 CPU0 reset status \n");
        }
    }

    /* Set the entry point */
    if (0U == entryPoint)
    {
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE, 0x10000U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE + 0x4U, 0x9U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE + 0x8U, 0xE7FEE7FEU);
    }
    else
    {
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE, 0x10000U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE + 0x4U, entryPoint);
    }

    if ((SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode) || (0U != entryPoint))
    {
        /* Bring IPU1 CPU0 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST,
                                   PM_TIMEOUT_INFINITE);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to release IPU1 CPU0 Reset \n");
        }

        /* Check the status of IPU1 module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_IPU1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibIPU1CPU1BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    int32_t  retVal    = 0;
    uint32_t rstStatus = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;

    /* Assert the IPU1 CPU1 reset */
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU1 CPU1 reset \n");
    }

    /* Check the reset status and clear */
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU1_CPU1_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU1 CPU1 reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU1_CPU1_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to clear IPU1 CPU1 reset status \n");
        }
    }

    /* Set the entry point */
    if (0U == entryPoint)
    {
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE, 0x10000U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE + 0x4U, 0x9U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE + 0x8U, 0xE7FEE7FEU);
    }
    else
    {
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE, 0x10000U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU1_RAM_BASE + 0x4U, entryPoint);
    }

    if ((SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode) || (0U != entryPoint))
    {
        /* Bring IPU1 CPU1 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU1_RST,
                                   PM_TIMEOUT_INFINITE);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to release IPU1 CPU1 Reset \n");
        }

        /* Check the status of IPU1 module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_IPU1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibIPU2CPU0BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    int32_t  retVal    = 0;
    uint32_t rstStatus = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;

    /* Assert the IPU2 CPU0 reset */
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_CPU0_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU2 CPU0 reset \n");
    }

    /* Check the reset status and clear */
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_CPU0_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU2 CPU0 reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_CPU0_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to clear IPU2 CPU0 reset status \n");
        }
    }

    /* Set the entry point */
    if (0U == entryPoint)
    {
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE, 0x10000U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE + 0x4U, 0x9U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE + 0x8U, 0xE7FEE7FEU);
    }
    else
    {
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE, 0x10000U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE + 0x4U, entryPoint);
    }

    if ((SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode) || (0U != entryPoint))
    {
        /* Bring IPU2 CPU0 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU2_CPU0_RST,
                                   PM_TIMEOUT_INFINITE);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to release IPU2 CPU0 Reset \n");
        }

        /* Check the status of IPU2 module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_IPU2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibIPU2CPU1BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    int32_t  retVal    = 0;
    uint32_t rstStatus = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;

    /* Assert the IPU2 CPU1 reset */
    retVal = PMHALResetAssert(PMHAL_PRCM_RG_IPU2_CPU1_RST);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to assert IPU2 CPU1 reset \n");
    }

    /* Check the reset status and clear */
    retVal = PMHALResetGetStatus(PMHAL_PRCM_RG_IPU2_CPU1_RST, &rstStatus);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to get IPU2 CPU1 reset status \n");
    }
    if (0x1U == rstStatus)
    {
        retVal = PMHALResetClearStatus(PMHAL_PRCM_RG_IPU2_CPU1_RST);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to clear IPU2 CPU1 reset status \n");
        }
    }

    /* Set the entry point */
    if (0U == entryPoint)
    {
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE, 0x10000U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE + 0x4U, 0x9U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE + 0x8U, 0xE7FEE7FEU);
    }
    else
    {
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE, 0x10000U);
        HW_WR_REG32(SBLLIB_SOC_L3_IPU2_RAM_BASE + 0x4U, entryPoint);
    }

    if ((SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode) || (0U != entryPoint))
    {
        /* Bring IPU2 CPU1 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_IPU2_CPU1_RST,
                                   PM_TIMEOUT_INFINITE);
        if (STW_SOK != retVal)
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n Failed to release IPU2 CPU1 Reset \n");
        }

        /* Check the status of IPU2 module mode*/
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_IPU2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibIPUBringUp(uint32_t ipuId,
                      uint32_t entryPointCPU0,
                      uint32_t entryPointCPU1,
                      uint32_t sblBuildMode)
{
    if (SBLLIB_CORE_ID_IPU1 == ipuId)
    {
        /* Release the slave cores out of reset */
        SBLLibIPU1CPU0BringUp(entryPointCPU0, sblBuildMode);
        SBLLibIPU1CPU1BringUp(entryPointCPU1, sblBuildMode);

        /* Cut clocks for IPU1 if entry point is zero for both cores */
        if ((0U == entryPointCPU0) &&
            (0U == entryPointCPU1) &&
            (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
        {
            PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                               PMHAL_PRCM_MODULE_MODE_DISABLED,
                               PM_TIMEOUT_INFINITE);

            PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU1,
                                  PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                  PM_TIMEOUT_INFINITE);

            PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST,
                              PM_TIMEOUT_NOWAIT);

            PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU1_RST,
                              PM_TIMEOUT_NOWAIT);
        }
    }
    else if (SBLLIB_CORE_ID_IPU2 == ipuId)
    {
        /* Release the slave cores out of reset */
        SBLLibIPU2CPU0BringUp(entryPointCPU0, sblBuildMode);
        SBLLibIPU2CPU1BringUp(entryPointCPU1, sblBuildMode);

        /* Cut clocks for IPU2 if entry point is zero for both cores */
        if ((0U == entryPointCPU0) &&
            (0U == entryPointCPU1) &&
            (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
        {
            PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU2,
                               PMHAL_PRCM_MODULE_MODE_DISABLED,
                               PM_TIMEOUT_INFINITE);

            PMHALCMSetCdClockMode(PMHAL_PRCM_CD_IPU2,
                                  PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                                  PM_TIMEOUT_INFINITE);

            PMHALResetRelease(PMHAL_PRCM_RG_IPU2_CPU0_RST,
                              PM_TIMEOUT_NOWAIT);

            PMHALResetRelease(PMHAL_PRCM_RG_IPU2_CPU1_RST,
                              PM_TIMEOUT_NOWAIT);
        }
    }
    else
    {
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n Tried to bring up unknown IPU \n");
    }
}

void SBLLibDSP1BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    uint32_t index = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
    int32_t  retVal = STW_SOK;

    /*Check if entry point is 1KB(0x400 byte) aligned */
    if (0U != entryPoint)
    {
        if ((uint32_t) 0U != (entryPoint & (0x000003FFU)))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n DSP1 entry point address is not aligned - App boot-up fails \n");
            entryPoint = 0U;
        }
    }

    /* Set the entry point. Set appropriate instructions to put DSP1 in idle
     * mode so as to power down the DSP1 Power Domain in Production
     * Build Mode when there is no App Image.
     */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Op code for the following assembly code: This makes the DSP
         * branch to address 0x200 offset from L2 RAM.
         *  B.S2  0x800200
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         */
        uint32_t dspInstruction1[8U] =
        {0x00004012U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};

        /* Op code for the following assembly code. This code sets the
         * PDCCMD DSP Sleep mode and then executes IDLE.
         *  MVK.L1   0,A3
         *  MVKH.S1  0x1810000,A3
         *  LDW.D1T1 *+A3[0],A3
         *  MVK.L2   0,B4
         *  MVKH.S2  0x1810000,B4
         *  NOP
         *  NOP
         *  SET.S1   A3,16,16,A3
         *  STW.D2T1 A3,*+B4[0]
         *  IDLE
         */
        uint32_t dspInstruction2[16U] =
        {0x0180A358U, 0x0180C0E8U, 0x018C0264U, 0x0200A35AU,
         0x0200C0EAU, 0x00000000U, 0x00000000U, 0x018E1088U,
         0x019002F4U, 0x00000000U, 0x00000000U, 0x00000000U,
         0x0001E000U, 0x0001E000U, 0x0001E000U, 0x00000000U};

        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP1_RST_VECT,
            (SBL_LIB_DSP1_BOOT_ADDRESS_VAL) >> 0xAU);

        for (index = 0U; index < 8U; index++)
        {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + (4U * index),
                        dspInstruction1[index]);
        }

        for (index = 0U; index < 16U; index++)
        {
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + (0x200U + (4U * index)),
                        dspInstruction2[index]);
        }
    }
    else if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode))
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP1_RST_VECT,
            (SBL_LIB_DSP1_BOOT_ADDRESS_VAL) >> 0xAU);
        for (index = 0U; index < 8U; index++)
        {
            /* Write Self Branch Instruction */
            HW_WR_REG32(SOC_DSP1_L2_SRAM_BASE + (4U * index), 0x12U);
        }
    }
    else
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP1_RST_VECT,
            entryPoint >> 0xAU);
    }

    /* Bring DSP1 out of reset */
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_DSP1_RST, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release DSP1 reset \n");
    }

    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Power Down the DSP1 power domain */
        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSP1,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_DSP1,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_DSP1,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of DSP1 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_DSP1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
#if defined (__ARM_ARCH_7A__)
void SBLLibMPUCPU1BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    pmhalMpuLprmHgRampParams_t hgRampParam = {1, 0};

    if (0U != entryPoint)
    {
        /* Write the entry point into AUXBOOT1 */
        HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_AUX_CORE_BOOT_1, entryPoint);

        /* Write the enable indicator into AUXBOOT0 */
        HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_AUX_CORE_BOOT_0, 0x10U);

        /* Send event to wake up CPU1 */
        SblLibSendEvent();
    }
    else
    {
        if (SBLLIB_SBL_BUILD_MODE_DEV != sblBuildMode)
        {
            /* Enable Hg/FastRamp-up in Retention */
            PMHALMpuLprmSetHgRampParams(&hgRampParam);
            PMHALMpuLprmSetMercuryRetention();

            /* Disable WUGEN */
            HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_A_1, 0);
            HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_B_1, 0);
            HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_C_1, 0);
            HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_D_1, 0);
            HW_WR_REG32(SOC_MPU_WUGEN_BASE + MPU_WKG_ENB_E_1, 0);

            /* Flushing the DCache is required to ensure CPU0 does not get
             * pipeline stalled when the cache is enabled later and the
             * cache invalidate is performed.
             */
            SblLibCP15DCacheCleanFlush();
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                         "\n Putting MPU CPU1 in Off mode \n");
            PMLIBCpu1ForcedOff();
        }
    }
}

#endif

void SBLLibDSP2BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    uint32_t index = 0U;
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
    int32_t  retVal = STW_SOK;

    /*Check if entry point is 1KB(0x400 byte) aligned */
    if (0U != entryPoint)
    {
        if ((uint32_t) 0U != (entryPoint & (0x000003FFU)))
        {
            SBLLibPrintf(
                SBLLIB_TRACE_LEVEL_ERROR,
                "\n DSP2 entry point address is not aligned - App boot-up fails \n");
            entryPoint = 0U;
        }
    }

    /* Set the entry point. Set appropriate instructions to put DSP2 in idle
     * mode so as to power down the DSP1 Power Domain in Production
     * Build Mode when there is no App Image.
     */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Op code for the following assembly code: This makes the DSP
         * branch to address 0x200 offset from L2 RAM.
         *  B.S2  0x800200
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         *  NOP
         */
        uint32_t dspInstruction1[8U] =
        {0x00004012U, 0U, 0U, 0U, 0U, 0U, 0U, 0U};

        /* Op code for the following assembly code. This code sets the
         * PDCCMD DSP Sleep mode and then executes IDLE.
         *  MVK.L1   0,A3
         *  MVKH.S1  0x1810000,A3
         *  LDW.D1T1 *+A3[0],A3
         *  MVK.L2   0,B4
         *  MVKH.S2  0x1810000,B4
         *  NOP
         *  NOP
         *  SET.S1   A3,16,16,A3
         *  STW.D2T1 A3,*+B4[0]
         *  IDLE
         */
        uint32_t dspInstruction2[16U] =
        {0x0180A358U, 0x0180C0E8U, 0x018C0264U, 0x0200A35AU,
         0x0200C0EAU, 0x00000000U, 0x00000000U, 0x018E1088U,
         0x019002F4U, 0x00000000U, 0x00000000U, 0x00000000U,
         0x0001E000U, 0x0001E000U, 0x0001E000U, 0x00000000U};

        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP2_RST_VECT,
            (SBL_LIB_DSP2_BOOT_ADDRESS_VAL) >> 0xAU);

        for (index = 0U; index < 8U; index++)
        {
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + (4U * index),
                        dspInstruction1[index]);
        }

        for (index = 0U; index < 16U; index++)
        {
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + (0x200U + (4U * index)),
                        dspInstruction2[index]);
        }
    }
    else if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode))
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP2_RST_VECT,
            (SBL_LIB_DSP2_BOOT_ADDRESS_VAL) >> 0xAU);
        for (index = 0U; index < 8U; index++)
        {
            /* Write Self Branch Instruction */
            HW_WR_REG32(SOC_DSP2_L2_SRAM_BASE + (4U * index), 0x12U);
        }
    }
    else
    {
        HW_WR_REG32(
            SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
            CTRL_CORE_CONTROL_DSP2_RST_VECT,
            entryPoint >> 0xAU);
    }

    /* Bring DSP2 out of reset */
    retVal = PMHALResetRelease(PMHAL_PRCM_RG_DSP2_RST, PM_TIMEOUT_INFINITE);
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                     "\n Failed to release DSP2 reset \n");
    }

    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        /* Power Down the DSP2 power domain */
        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_DSP2,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALModuleModeSet(PMHAL_PRCM_MOD_DSP2,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_DSP2,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of DSP2 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_DSP2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibEVE1BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
    int32_t retVal = STW_SOK;

    if (0U != entryPoint)
    {
        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_L3_EVE1_MMU0_BASE, entryPoint);
        /* Bring EVE1 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE1_CPU_RST, PM_TIMEOUT_INFINITE);
    }
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode))
    {
        /* Assuming SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE i.e. 0x80000000U is
         * not in use. Reset vector points to
         * SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE i.e. 0x80000100U */
        HW_WR_REG32(SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE,
                    SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE);

        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE, 0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x4U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x8U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0xCU,
                    0x0000037FU);

        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_L3_EVE1_MMU0_BASE,
                           SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE);
        /* Bring EVE1 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE1_CPU_RST, PM_TIMEOUT_INFINITE);
    }
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                    "\n Failed to release EVE1 reset \n");
    }
    /* Power Down the EVE Power Domain in Production Build Mode
     * when there is no App Image */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE1,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_NOWAIT);
        /* Assert the reset */
        retVal = PMHALResetAssert(PMHAL_PRCM_RG_EVE1_RST);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE1,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE1,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of EVE1 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE1, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibEVE2BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
    int32_t retVal = STW_SOK;

    if (0U != entryPoint)
    {
        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_L3_EVE2_MMU0_BASE, entryPoint);
        /* Bring EVE2 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE2_CPU_RST, PM_TIMEOUT_INFINITE);
    }
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode))
    {
        /* Assuming SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE i.e. 0x80000000U is
         * not in use. Reset vector points to
         * SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE i.e. 0x80000100U */
        HW_WR_REG32(SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE,
                    SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE);

        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE, 0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x4U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x8U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0xCU,
                    0x0000037FU);

        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_L3_EVE2_MMU0_BASE,
                           SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE);
        /* Bring EVE2 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE2_CPU_RST, PM_TIMEOUT_INFINITE);
    }
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                    "\n Failed to release EVE2 reset \n");
    }
    /* Power Down the EVE Power Domain in Production Build Mode
     * when there is no App Image */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE2,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_NOWAIT);
        /* Assert the reset */
        retVal = PMHALResetAssert(PMHAL_PRCM_RG_EVE2_RST);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE2,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE2,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of EVE2 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE2, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}
#endif
#if defined (SOC_TDA2XX)
void SBLLibEVE3BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
    int32_t retVal = STW_SOK;

    if (0U != entryPoint)
    {
        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_L3_EVE3_MMU0_BASE, entryPoint);
        /* Bring EVE3 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE3_CPU_RST, PM_TIMEOUT_INFINITE);
    }
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode))
    {
        /* Assuming SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE i.e. 0x80000000U is
         * not in use. Reset vector points to
         * SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE i.e. 0x80000100U */
        HW_WR_REG32(SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE,
                    SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE);

        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE, 0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x4U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x8U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0xCU,
                    0x0000037FU);

        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_L3_EVE3_MMU0_BASE,
                           SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE);
        /* Bring EVE3 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE3_CPU_RST, PM_TIMEOUT_INFINITE);
    }
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                    "\n Failed to release EVE3 reset \n");
    }
    /* Power Down the EVE Power Domain in Production Build Mode
     * when there is no App Image */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE3,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_NOWAIT);
        /* Assert the reset */
        retVal = PMHALResetAssert(PMHAL_PRCM_RG_EVE3_RST);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE3,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE3,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of EVE3 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE3, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

void SBLLibEVE4BringUp(uint32_t entryPoint, uint32_t sblBuildMode)
{
    pmhalPrcmModuleSIdleState_t sIdleState =
        PMHAL_PRCM_MODULE_SIDLESTATE_DISABLED;
    int32_t retVal = STW_SOK;

    if (0U != entryPoint)
    {
        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_L3_EVE4_MMU0_BASE, entryPoint);
        /* Bring EVE4 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE4_CPU_RST, PM_TIMEOUT_INFINITE);
    }
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_DEV == sblBuildMode))
    {
        /* Assuming SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE i.e. 0x80000000U is
         * not in use. Reset vector points to
         * SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE i.e. 0x80000100U */
        HW_WR_REG32(SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE,
                    SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE);

        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE, 0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x4U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0x8U,
                    0x0000037FU);
        /* IDLE; Op Code for ARP32 */
        HW_WR_REG32(SBLLIB_EVE_RESET_VECTOR_ADDRESS_NO_IMAGE + 0xCU,
                    0x0000037FU);

        /* Set the EVE MMU and entry point */
        SblLibEVEMMUConfig(SBLLIB_SOC_L3_EVE4_MMU0_BASE,
                           SBLLIB_EVE_BOOT_ADDRESS_NO_IMAGE);
        /* Bring EVE4 out of reset */
        retVal = PMHALResetRelease(PMHAL_PRCM_RG_EVE4_CPU_RST, PM_TIMEOUT_INFINITE);
    }
    if (STW_SOK != retVal)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                    "\n Failed to release EVE4 reset \n");
    }
    /* Power Down the EVE Power Domain in Production Build Mode
     * when there is no App Image */
    if ((0U == entryPoint) && (SBLLIB_SBL_BUILD_MODE_PROD == sblBuildMode))
    {
        PMHALModuleModeSet(PMHAL_PRCM_MOD_EVE4,
                           PMHAL_PRCM_MODULE_MODE_DISABLED,
                           PM_TIMEOUT_NOWAIT);
        /* Assert the reset */
        retVal = PMHALResetAssert(PMHAL_PRCM_RG_EVE4_RST);

        PMHALCMSetCdClockMode(PMHAL_PRCM_CD_EVE4,
                              PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                              PM_TIMEOUT_INFINITE);

        PMHALPdmSetPDState(PMHAL_PRCM_PD_EVE4,
                           PMHAL_PRCM_PD_STATE_OFF,
                           PM_TIMEOUT_INFINITE);
    }
    else
    {
        /* Check the status of EVE4 Module Mode */
        do
        {
            PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_EVE4, &sIdleState);
        }
        while (sIdleState != PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL);
    }
}

#endif

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX)
static void SblLibEVEMMUConfig(uint32_t baseAddr, uint32_t entryPoint)
{
    MMU_TlbEntry_t mmuEntry       = {0U};
    uint32_t       entryPointPage = 0U;

    /* Derive entry point page for given entry point */
    entryPointPage = entryPoint & (0xFF000000U);

    /* Configure MMU TLB entry for Vector table  as 1MB section */
    /* EVE starts executing from virtual address 0x0 when brought out of reset.
     * When SBL maps the 0x0 to entryPointPage, it assumes that the vector
     * table is present at entryPointPage.
     * E.g. If entry point is 0x81F62648, entryPointPage is calculated as
     * 0x81000000 and application image should be built in a way that vector
     * table is present at this address.
     */
    mmuEntry.phyAddr        = entryPoint & SBLLibEVEGetVecTablePageMask();
    mmuEntry.virtAddr       = 0x00000000U;
    mmuEntry.valid          = (uint32_t) TRUE;
    mmuEntry.pageSize       = MMU_Section_Size;
    mmuEntry.endianness     = MMU_Little_Endian;
    mmuEntry.elementSize    = MMU_NoTranslation_ElementSize;
    mmuEntry.tlbElementSize = MMU_CPU_ElementSize;
    mmuEntry.preserve       = (uint32_t) TRUE;
    MMUTlbEntrySet(baseAddr, (uint32_t) 1U, &mmuEntry);

    /*
     * Configure MMU TLB entry for code & data section  as 16MB super
     * section
     */
    mmuEntry.phyAddr        = entryPointPage;
    mmuEntry.virtAddr       = entryPointPage;
    mmuEntry.valid          = (uint32_t) TRUE;
    mmuEntry.pageSize       = MMU_SuperSection_Size;
    mmuEntry.endianness     = MMU_Little_Endian;
    mmuEntry.elementSize    = MMU_NoTranslation_ElementSize;
    mmuEntry.tlbElementSize = MMU_CPU_ElementSize;
    mmuEntry.preserve       = (uint32_t) TRUE;
    MMUTlbEntrySet(baseAddr, (uint32_t) 2U, &mmuEntry);

    /*
     * Configure MMU TLB entry for EVE's internal memory  as 16MB super
     * section
     */
    mmuEntry.phyAddr        = SBLLIB_SOC_EVE_DMEM_BASE;
    mmuEntry.virtAddr       = SBLLIB_SOC_EVE_DMEM_BASE;
    mmuEntry.valid          = (uint32_t) TRUE;
    mmuEntry.pageSize       = MMU_SuperSection_Size;
    mmuEntry.endianness     = MMU_Little_Endian;
    mmuEntry.elementSize    = MMU_NoTranslation_ElementSize;
    mmuEntry.tlbElementSize = MMU_CPU_ElementSize;
    mmuEntry.preserve       = (uint32_t) TRUE;
    MMUTlbEntrySet(baseAddr, (uint32_t) 3U, &mmuEntry);

    /*
     * Configure MMU TLB entry for L4PER1, L4PER2 and L4PER3 as 16MB super
     * section
     */
    mmuEntry.phyAddr        = SOC_L4_PER_AP_BASE;
    mmuEntry.virtAddr       = SOC_L4_PER_AP_BASE;
    mmuEntry.valid          = (uint32_t) TRUE;
    mmuEntry.pageSize       = MMU_SuperSection_Size;
    mmuEntry.endianness     = MMU_Little_Endian;
    mmuEntry.elementSize    = MMU_NoTranslation_ElementSize;
    mmuEntry.tlbElementSize = MMU_CPU_ElementSize;
    mmuEntry.preserve       = (uint32_t) TRUE;
    MMUTlbEntrySet(baseAddr, (uint32_t) 4U, &mmuEntry);

    /* Enable MMU */
    MMUEnable(baseAddr);

    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO1,
        "\n EVE MMU configuration completed \n");
}

#if defined (__ARM_ARCH_7A__)

static void SblLibSendEvent(void)
{
    /* Send event to wake up CPU1, first set up Data Synchronization
     * Barrier and then send SEV */
    asm (" DSB");
    asm (" SEV");
}

static void SblLibCP15DCacheCleanFlush(void)
{
    asm ("    push    {r4-r11} \n\t"
         "    dmb \n\t"
         "    mrc    p15, #1, r0, c0, c0, #1 \n\t"  /* Load CLID register */
         "    ands    r3, r0, #0x7000000  \n\t"     /* Get LoC */
         "    mov    r3, r3, lsr #23 \n\t"
         "    beq    finished \n\t"                 /* if LoC is 0, then no need
                                                     *to clean */
         "    mov    r10, #0 \n\t"                  /* start cleaning at cache
                                                     *level 0 */
         "loop1: add    r2, r10, r10, lsr #1 \n\t"  /* work out 3x current cache
                                                     *level */
         "    mov    r1, r0, lsr r2 \n\t"           /* get cache type */
         "    and    r1, r1, #7 \n\t"               /* mask of the bits for
                                                     *current cache only*/
         "    cmp    r1, #2  \n\t"                  /* cache at this level */
         "    blt    skip \n\t"                     /* skip if no cache, or just
                                                     *i-cache */
         "    mcr    p15, #2, r10, c0, c0, #0 \n\t" /* select current cache
                                                     * level
                                                     **/
         "    isb \n\t"                             /* isb to sych the new CSSR
                                                     * &
                                                     *CSIDR */
         "    mrc    p15, #1, r1, c0, c0, #0 \n\t"  /* read the new CSIDR */
         "    and    r2, r1, #7 \n\t"               /* extract the length of the
                                                     *cache lines */
         "    add    r2, r2, #4 \n\t"
         "    ldr    r4, =0x3ff \n\t"
         "    ands   r4, r4, r1, lsr #3 \n\t"        /* Max on the way size */
         "    clz    r5, r4 \n\t"                    /* find bit position of way
                                                      *size increment */
         "    ldr    r7, =0x7fff \n\t"
         "    ands    r7, r7, r1, lsr #13 \n\t"      /* Max number of the index
                                                      *size */
         "loop2: mov     r9, r4 \n\t"
         "loop3: orr     r11, r10, r9, lsl r5  \n\t" /* factor way and cache
                                                      *number */
         "    orr    r11, r11, r7, lsl r2 \n\t"      /* factor index number */
         "    mcr    p15, #0, r11, c7, c14, #2 \n\t" /* clean & invalidate by
                                                      *set/way */
         "    subs    r9, r9, #1 \n\t"               /* decrement the way */
         "    bge     loop3 \n\t"
         "    subs    r7, r7, #1 \n\t"               /* decrement the index */
         "    bge     loop2 \n\t"
         "skip: add     r10, r10, #2 \n\t"           /*  increment cache number
                                                     **/
         "    cmp     r3, r10 \n\t"
         "    bgt     loop1 \n\t"
         "finished: mov     r10, #0 \n\t"            /* switch back to cache
                                                      *level 0 */
         "    mcr     p15, #2, r10, c0, c0, #0 \n\t" /* select current cache
                                                      * level in csselr */
         "    isb \n\t"
         "    pop    {r4-r11} \n\t");
}

#endif
#endif

