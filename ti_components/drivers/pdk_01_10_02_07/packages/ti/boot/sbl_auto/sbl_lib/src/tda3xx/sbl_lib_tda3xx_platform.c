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
 *  \file     sbl_lib_tda3xx_platform.c
 *
 *  \brief    This file contains the SBL Library layer for tda3xx platform.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/cslr_mmu.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_mmu.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/csl_tesoc.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_config.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>
#include <sbl_lib_tda3xx_priv.h>
#include <ti/drv/pm/pmhal.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Timer Start Count Value */
#define SBL_LIB_TIMER_START_COUNT                      ((uint32_t) 0x00000000U)

/* Timer count at which IPU is powered down. 0x2D0 -> 36 micro-seconds */
#define SBL_LIB_TIMER_IPU_POWER_DOWN_COUNT             ((uint32_t) 0x000002D0U)

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

/**
 * \brief   This API does a sequence of writes after which IPU can be put in
 *          IDLE state by sending WFI.
 *
 * \param   None
 *
 * \return  None
 *
 * \note    This API will only prepare IPU to be put in IDLE state. To actually
 *          put IPU in IDLE state send "WFI" instruction immediately after
 *          calling this API.
 */
static void SblLibSetIPUIdle(void);

/**
 * \brief   This function waits for the interrupt i.e. WFI.
 *
 * \param   None.
 *
 * \return  None.
 */
static inline void SblLibWaitForInterrupt(void);

/**
 * \brief   This function configures the EVE MMU as per EVE's entry point.
 *          Contains entries to access entry location page, L4 peripheral
 *          space and internal memories. Remaining DDR entries should be
 *          taken care by application.
 *
 * \param   baseAddr       Base address of EVE MMU.
 * \param   entryPoint     Entry Point of EVE.
 *
 * \retval  None.
 */
static void SblLibEVEMMUConfig(uint32_t baseAddr, uint32_t entryPoint);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Global variable for referencing the Boot Media App Image Read function */
static SBLLibMediaReadFxn        gMediaReadFxn = NULL;

/* Global variable for referencing the DDR App Image Read function */
static SBLLibDDRReadFxn          gDDRReadFxn = NULL;

/*
 * Global variable for referencing the location upto which App Image has been
 * read
 */
static SBLLibSeekFxn             gSeekFxn = NULL;

/* Global variable for referencing the CRC Calculation function */
static SBLLibCalculateCRCFxn     gCalculateCRCFxn = NULL;

/* Global variable for referencing the RPRC authentication function */
static SBLLibAuthenticateRPRCFxn gAuthenticateRPRCFxn = NULL;

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
    uint32_t       fileNo, entryPoint = 0U, address = 0U;
    uint32_t       magicStrHdrStart = SBLLIB_META_HEADER_MAGIC_STR;
    uint32_t       magicStrHdrEnd   = SBLLIB_META_HEADER_MAGIC_END;
    uint32_t       currAppImageAddr = imageParams->appImageOffset;
    int32_t        retVal           = STW_SOK;
    uint32_t       crcDataSize      = 0U, tempAddr = 0U;
    uint32_t       crcSrcAddr       = 0U;
    uint32_t       tempHeaderAddr   = 0U, isHeaderAppended = 0U;
    crcSignature_t crcSignValue     = {0U};
    crcSignature_t validCrcSign[SBLLIB_MAX_RPRC_IMAGES + 1U];
    uint32_t       loopCnt       = 0U;
    char           coreIdStr[10U] = {0};

    for (loopCnt = 0U; loopCnt <= SBLLIB_MAX_RPRC_IMAGES; loopCnt++)
    {
        validCrcSign[loopCnt].regL = 0U;
        validCrcSign[loopCnt].regH = 0U;
    }
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
                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_IMP_INFO,
                    "\nTrying to boot App Image with header version 1\r\n");
                SBLLibMultiCoreImageParseV1(imageParams);
            }
            else
            {
                if ((uint32_t) TRUE == imageParams->enableCrc)
                {
                    /* Assign signatures before modifying header */
                    /* Assign meta header signature */
                    validCrcSign[0].regL =
                        imageParams->appImgMetaHeaderV2->
                        metaHeaderStartV2.metaHeaderCrcL;
                    validCrcSign[0].regH =
                        imageParams->appImgMetaHeaderV2->
                        metaHeaderStartV2.metaHeaderCrcH;

                    imageParams->appImgMetaHeaderV2->metaHeaderStartV2.
                    metaHeaderCrcL
                        = 0x0U;
                    imageParams->appImgMetaHeaderV2->metaHeaderStartV2.
                    metaHeaderCrcH
                        = 0x0U;

                    /* Assign RPRC Signatures */
                    for (fileNo = 0U;
                         fileNo <
                         imageParams->appImgMetaHeaderV2->metaHeaderStartV2.
                         numFiles;
                         fileNo++)
                    {
                        validCrcSign[fileNo + 1U].regL =
                            imageParams->appImgMetaHeaderV2->
                            metaHeaderCoreV2[fileNo].rprcImageCrcL;

                        validCrcSign[fileNo + 1U].regH =
                            imageParams->appImgMetaHeaderV2->
                            metaHeaderCoreV2[fileNo].rprcImageCrcH;

                        imageParams->appImgMetaHeaderV2->
                        metaHeaderCoreV2[fileNo].rprcImageCrcH = 0x0U;

                        imageParams->appImgMetaHeaderV2->
                        metaHeaderCoreV2[fileNo].rprcImageCrcL = 0x0U;
                    }

                    if (NULL == gCalculateCRCFxn)
                    {
                        SBLLibPrintf(
                            SBLLIB_TRACE_LEVEL_ERROR,
                            "CRC callback is not registered, aborting boot\r\n");
                        SBLLibAbortBoot();
                    }

                    /* Check if Meta Header contains 0x00000000 in the end for 8
                     * byte alignment
                     */
                    if (currAppImageAddr !=
                        imageParams->appImgMetaHeaderV2->
                        metaHeaderCoreV2[0].imageOffset)
                    {
                        tempAddr =
                            (currAppImageAddr - imageParams->appImageOffset)
                            + (uint32_t) (&imageParams->appImgMetaHeaderV2
                                          ->
                                          metaHeaderStartV2.magicStr);
                        *(volatile uint32_t *) tempAddr = 0x0U;

                        currAppImageAddr += 0x4U;
                        isHeaderAppended  = 1U;
                    }

                    crcDataSize = currAppImageAddr -
                                  imageParams->appImageOffset;
                    crcSrcAddr =
                        (uint32_t) (&imageParams->appImgMetaHeaderV2->
                                    metaHeaderStartV2.magicStr);

                    if (SBLLIB_MAX_RPRC_IMAGES !=
                        imageParams->appImgMetaHeaderV2->metaHeaderStartV2.
                        numFiles)
                    {
                        if (1U == isHeaderAppended)
                        {
                            tempHeaderAddr = (crcSrcAddr + crcDataSize) - 0xCU;
                            *(volatile uint32_t *) tempHeaderAddr = 0x0U;
                            tempHeaderAddr = (crcSrcAddr + crcDataSize) - 0x8U;
                            *(volatile uint32_t *) tempHeaderAddr =
                                imageParams->appImgMetaHeaderV2->metaHeaderEnd.
                                magicStringEnd;
                        }
                        else
                        {
                            tempHeaderAddr = (crcSrcAddr + crcDataSize) - 0x8U;
                            *(volatile uint32_t *) tempHeaderAddr = 0x0U;
                            tempHeaderAddr = (crcSrcAddr + crcDataSize) - 0x4U;
                            *(volatile uint32_t *) tempHeaderAddr =
                                imageParams->appImgMetaHeaderV2->metaHeaderEnd.
                                magicStringEnd;
                        }
                    }

                    /* Calculate CRC */
                    gCalculateCRCFxn((const void *) crcSrcAddr,
                                     crcDataSize,
                                     &crcSignValue);

                    if ((validCrcSign[0].regL != crcSignValue.regL) ||
                        (validCrcSign[0].regH != crcSignValue.regH))
                    {
                        SBLLibPrintf(
                            SBLLIB_TRACE_LEVEL_ERROR,
                            "\n Multi-Core Header CRC Match Failed, Aborting Boot\n");
                        SBLLibAbortBoot();
                    }
                }

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

                        if (0U == imageParams->skipDDRCopy)
                        {
                            address = imageParams->ddrAppImageAddress;
                        }
                        else
                        {
                            address = currAppImageAddr;
                        }

                        if ((uint32_t) TRUE == imageParams->enableCrc)
                        {
                            crcDataSize = imageParams->appImgMetaHeaderV2->
                                          metaHeaderCoreV2[fileNo].
                                          rprcImageSize;
                            crcSrcAddr = address;

                            /* Calculate CRC */
                            gCalculateCRCFxn((const void *) crcSrcAddr,
                                             crcDataSize,
                                             &crcSignValue);

                            if ((validCrcSign[fileNo + 1U].regL !=
                                 crcSignValue.regL) ||
                                (validCrcSign[fileNo + 1U].regH !=
                                 crcSignValue.regH))
                            {
                                SBLLibConvertHexToString(
                                    imageParams->appImgMetaHeaderV2->
                                    metaHeaderCoreV2[fileNo].coreId,
                                    &coreIdStr[0U]);
                                SBLLibPrintf(
                                    SBLLIB_TRACE_LEVEL_ERROR,
                                    "\n CRC Match Failed for Core ID:");
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             coreIdStr);
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             ", Aborting Boot\n");
                                SBLLibAbortBoot();
                            }
                        }
                        else
                        {
                            /* Using crcDataSize as a temporary variable */
                            crcDataSize =
                                imageParams->appImgMetaHeaderV2->
                                metaHeaderCoreV2[fileNo].rprcImageSize;
                            retVal =
                                gAuthenticateRPRCFxn(address, crcDataSize);
                            if (STW_SOK != retVal)
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "\n Un-authenticated image \n");
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "\n Aborting Boot \n");
                                SBLLibAbortBoot();
                            }
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
                if ((rprcHeader->rprcSectionHeader.loadAddr >=
                     SOC_OCMC_RAM1_BASE) &&
                    (rprcHeader->rprcSectionHeader.loadAddr <
                     (SOC_OCMC_RAM1_BASE + SBLLIB_SOC_OCMC_RAM1_SIZE)))
                {
                    /* Internal OCMC RAM Space for all the cores */
                }
                else if (rprcHeader->rprcSectionHeader.loadAddr < 0x80000000U)
                {
                    switch (coreId)
                    {
                        case SBLLIB_CORE_ID_IPU1:
                        case SBLLIB_CORE_ID_IPU1_CPU0:
                        case SBLLIB_CORE_ID_IPU1_CPU1:
                            if (rprcHeader->rprcSectionHeader.loadAddr <
                                0x10000U)
                            {
                                rprcHeader->rprcSectionHeader.loadAddr =
                                    SBLLIB_SOC_L3_IPU1_RAM_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
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
                                    SBLLIB_SOC_L3_EVE_DMEM_BASE +
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
                                    SBLLIB_SOC_L3_EVE_WBUF_BASE +
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
                                    SBLLIB_SOC_L3_EVE_IBUF_LA_BASE +
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
                                    SBLLIB_SOC_L3_EVE_IBUF_HA_BASE +
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
                                    SBLLIB_SOC_L3_EVE_IBUF_LB_BASE +
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
                                    SBLLIB_SOC_L3_EVE_IBUF_HB_BASE +
                                    rprcHeader->rprcSectionHeader.loadAddr;
                            }
                            else
                            {
                                SBLLibPrintf(SBLLIB_TRACE_LEVEL_ERROR,
                                             "EVE1 - Invalid Memory section");
                            }
                            break;
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
    int32_t deviceId;

    deviceId = 77;

    return deviceId;
}

int32_t SBLLibBootCore(uint32_t             entryPoint,
                       uint32_t             coreId,
                       sbllibEntryPoints_t *entryPoints)
{
    int32_t retVal = STW_SOK;

    switch (coreId)
    {
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
            /* In case of Fully Optimized SBL, IPU Core1 needs to be booted up
             * before loading other cores for responding to CAN
             */
            #if (SBL_OPT_LEVEL >= SBLLIB_OPT_LEVEL_HIGH)
            /* Set the entry point for IPU1 Core 1 */
            if (0U != entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU1])
            {
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_IMP_INFO,
                             "\n Jumping to IPU1 CPU1 App \n");
                HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS,
                            entryPoints->entryPoint[
                                SBLLIB_CORE_ID_IPU1_CPU1]);
            }
            else
            {
                /* Set while(1) loop */
                HW_WR_REG32((SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE - 1U),
                            0xE7FEE7FEU);

                SBLLibPrintf(
                    SBLLIB_TRACE_LEVEL_IMP_INFO,
                    "\n No IPU1 CPU1 App Found, Switching to while Loop \n");
                HW_WR_REG32(SBLLIB_IPU1_CORE_1_ENTRY_POINT_ADDRESS,
                            SBLLIB_IPU1_CORE1_BOOT_ADDRESS_NO_IMAGE);
            }
            #endif
            break;

        case SBLLIB_CORE_ID_DSP1:
            /* DSP1 */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n DSP1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_DSP1] = entryPoint;
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
        case SBLLIB_CORE_ID_IPU1:
            /* IPU1 SMP */
            SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                         "\n IPU1 CPU0 and CPU1 Image Load Completed \n");
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU0] =
                entryPoint;
            entryPoints->entryPoint[SBLLIB_CORE_ID_IPU1_CPU1] =
                entryPoint;
            break;
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
    /* Reset DSP1 */
    SBLLibCPUReset(SBLLIB_CORE_ID_DSP1);

    /* Reset DSP2 */
    SBLLibCPUReset(SBLLIB_CORE_ID_DSP2);

    /* Reset EVE1 */
    SBLLibCPUReset(SBLLIB_CORE_ID_EVE1);
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

        case SBLLIB_CORE_ID_DSP2:
            systemReset = PMHAL_PRCM_RG_DSP2_SYS_RST;
            localReset  = PMHAL_PRCM_RG_DSP2_RST;
            break;

        case SBLLIB_CORE_ID_EVE1:
            systemReset = PMHAL_PRCM_RG_EVE1_RST;
            localReset  = PMHAL_PRCM_RG_EVE1_CPU_RST;
            break;

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

int32_t SBLLibRunTesocTest(uint32_t              testId,
                           const tesocTestCfg_t *tesocTestConfig)
{
    int32_t  retVal = STW_SOK;
    pmhalPrcmModuleSIdleState_t idleState;
    pmhalPrcmModuleMStbyState_t standbyState;
    uint32_t siliconRev = SBLLibGetSiliconRev();

    if (siliconRev < 3U)
    {
        /*
         * TESOC BISTs are only supported for SR 2.0 and later silicon revisions
         * For more details refer to ADAS Silicon Revision 1.0, 1.0A (SPRZ425)
         * (Errata ID:i888).
         */
        SBLLibPrintf(
            SBLLIB_TRACE_LEVEL_ERROR,
            "\n TESOC BISTs not supported for this Silicon Rev, Aborting Boot\n");
        SBLLibAbortBoot();
    }
    else
    {
        switch (testId)
        {
            case TESOC_TEST_ID_IPU:
                if (TRUE == tesocTestConfig->completionIntrEnable)
                {
                    /* Configure TESOC Interrupt */
                    TESOCIntrEnable(SOC_TESOC_BASE,
                                    TESOC_INTR_FLAG_TEST_COMPLETION);
                }

                /* Clear TESOC status registers */
                retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                             tesocTestConfig->domainLabel);

                /* Configure TESOC and start the test */
                retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC IPU BIST Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                /* Disable other modules in IPU clock domain */
                retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_MCASP1,
                                            PMHAL_PRCM_MODULE_MODE_DISABLED,
                                            PM_TIMEOUT_NOWAIT);
                retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER5,
                                             PMHAL_PRCM_MODULE_MODE_DISABLED,
                                             PM_TIMEOUT_NOWAIT);
                retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER6,
                                             PMHAL_PRCM_MODULE_MODE_DISABLED,
                                             PM_TIMEOUT_NOWAIT);
                retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER7,
                                             PMHAL_PRCM_MODULE_MODE_DISABLED,
                                             PM_TIMEOUT_NOWAIT);
                retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_TIMER8,
                                             PMHAL_PRCM_MODULE_MODE_DISABLED,
                                             PM_TIMEOUT_NOWAIT);
                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to disable modules in IPU domain, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                /* Power down IPU for TESOC to start test */
                retVal = PMHALPdmSetPDState(PMHAL_PRCM_PD_IPU,
                                            PMHAL_PRCM_PD_STATE_OFF,
                                            PM_TIMEOUT_NOWAIT);

                retVal += PMHALCMSetCdClockMode(
                    PMHAL_PRCM_CD_IPU,
                    PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                    PM_TIMEOUT_NOWAIT);

                retVal += PMHALCMSetCdClockMode(
                    PMHAL_PRCM_CD_IPU1,
                    PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                    PM_TIMEOUT_NOWAIT);
                /*
                 * This is required as the force override bit
                 * CTRL_CORE_SEC_IPU_WAKEUP does not set the right values for
                 * the PRCM registers and when the override is lifted then cores
                 * are left in a bad power and reset state.
                 */
                retVal += PMHALResetRelease(PMHAL_PRCM_RG_IPU1_CPU0_RST,
                                            PM_TIMEOUT_NOWAIT);
                retVal += PMHALResetRelease(PMHAL_PRCM_RG_IPU1_RST,
                                            PM_TIMEOUT_NOWAIT);
                retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_IPU1,
                                             PMHAL_PRCM_MODULE_MODE_AUTO,
                                             PM_TIMEOUT_NOWAIT);

                retVal += PMHALPdmSetLastPDStatus(PMHAL_PRCM_PD_IPU,
                                                  PMHAL_PRCM_PD_STATE_ON_ACTIVE);

                retVal += PMHALResetAssert(PMHAL_PRCM_RG_IPU1_CPU1_RST);

                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to Power Down IPU, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
                /*
                 * Set last reset indicator as 0xA to identify TESOC reset
                 * 0xA: TESOC Reset
                 * TESOC reset indicator should be set after all test
                 * configuration is done to avoid async reset issue (warm
                 * reset asserted  after TESOC is configured for IPU field
                 * test or when test is running). This will minimise false
                 * partial boot window due to setting of reset indicator bit.
                 */
                HW_WR_FIELD32(
                    SOC_SEC_EFUSE_REGISTERS_BASE +
                    CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR,
                    CTRL_CORE_SEC_TESOC_LAST_RESET_INDICATOR_IPU,
                    0xA);

                /* Put IPU in IDLE state */
                SblLibSetIPUIdle();
                SblLibWaitForInterrupt();

                break;

            case TESOC_TEST_ID_EVE:
                /* Power down EVE for TESOC to start test */
                retVal = PMHALModuleModeSet(
                    PMHAL_PRCM_MOD_EVE1,
                    PMHAL_PRCM_MODULE_MODE_DISABLED,
                    PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMSetCdClockMode(
                    (pmhalPrcmCdId_t) PMHAL_PRCM_CD_EVE1,
                    PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                    PM_TIMEOUT_NOWAIT);

                retVal += PMHALResetAssert(PMHAL_PRCM_RG_EVE1_CPU_RST);
                retVal += PMHALResetAssert(PMHAL_PRCM_RG_EVE1_RST);

                retVal += PMHALPdmSetPDState(
                    PMHAL_PRCM_PD_EVE1,
                    PMHAL_PRCM_PD_STATE_OFF,
                    PM_TIMEOUT_NOWAIT);

                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to Power Down EVE, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                if (TRUE == tesocTestConfig->completionIntrEnable)
                {
                    /* Configure TESOC Interrupt */
                    TESOCIntrEnable(SOC_TESOC_BASE,
                                    TESOC_INTR_FLAG_TEST_COMPLETION);
                }

                /* Clear TESOC status registers */
                retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                             tesocTestConfig->domainLabel);

                /* Configure TESOC and start the test */
                retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

                /* Wait for TESOC to start test */
                retVal += TESOCWaitUntilBusy(SOC_TESOC_BASE,
                                             TESOC_TIMEOUT_TEST_START);
                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC Start EVE Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                /* Wait for TESOC test to complete */
                retVal = TESOCWaitUntilNotBusy(SOC_TESOC_BASE,
                                               TESOC_TIMEOUT_TEST_END);
                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC End EVE Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
                break;

            case TESOC_TEST_ID_DSP1:
                /*Power down DSP1 for TESOC to start test */
                retVal = PMHALModuleModeSet(
                    PMHAL_PRCM_MOD_DSP1,
                    PMHAL_PRCM_MODULE_MODE_DISABLED,
                    PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMSetCdClockMode(
                    (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP1,
                    PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                    PM_TIMEOUT_NOWAIT);

                retVal += PMHALResetAssert(PMHAL_PRCM_RG_DSP1_RST);
                retVal += PMHALResetAssert(PMHAL_PRCM_RG_DSP1_SYS_RST);

                retVal += PMHALPdmSetPDState(
                    PMHAL_PRCM_PD_DSP1,
                    PMHAL_PRCM_PD_STATE_OFF,
                    PM_TIMEOUT_NOWAIT);
                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to Power Down DSP1, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                if (TRUE == tesocTestConfig->completionIntrEnable)
                {
                    /* Configure TESOC Interrupt */
                    TESOCIntrEnable(SOC_TESOC_BASE,
                                    TESOC_INTR_FLAG_TEST_COMPLETION);
                }

                /* Clear TESOC status registers */
                retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                             tesocTestConfig->domainLabel);

                /* Configure TESOC and start the test */
                retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

                /* Wait for TESOC to start test */
                retVal += TESOCWaitUntilBusy(SOC_TESOC_BASE,
                                             TESOC_TIMEOUT_TEST_START);
                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC Start DSP1 Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                /* Wait for TESOC test to complete */
                retVal = TESOCWaitUntilNotBusy(SOC_TESOC_BASE,
                                               TESOC_TIMEOUT_TEST_END);
                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC End DSP1 Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
                break;

            case TESOC_TEST_ID_DSP2:
                /*Power down DSP2 for TESOC to start test */
                retVal = PMHALModuleModeSet(
                    PMHAL_PRCM_MOD_DSP2,
                    PMHAL_PRCM_MODULE_MODE_DISABLED,
                    PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMSetCdClockMode(
                    (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSP2,
                    PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                    PM_TIMEOUT_NOWAIT);

                retVal += PMHALResetAssert(PMHAL_PRCM_RG_DSP2_RST);
                retVal += PMHALResetAssert(PMHAL_PRCM_RG_DSP2_SYS_RST);

                retVal += PMHALPdmSetPDState(
                    PMHAL_PRCM_PD_DSP2,
                    PMHAL_PRCM_PD_STATE_OFF,
                    PM_TIMEOUT_NOWAIT);
                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to Power Down DSP2, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                if (TRUE == tesocTestConfig->completionIntrEnable)
                {
                    /* Configure TESOC Interrupt */
                    TESOCIntrEnable(SOC_TESOC_BASE,
                                    TESOC_INTR_FLAG_TEST_COMPLETION);
                }

                /* Clear TESOC status registers */
                retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                             tesocTestConfig->domainLabel);

                /* Configure TESOC and start the test */
                retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);

                /* Wait for TESOC to start test */
                retVal += TESOCWaitUntilBusy(SOC_TESOC_BASE,
                                             TESOC_TIMEOUT_TEST_START);
                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC Start DSP2 Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                /* Wait for TESOC test to complete */
                retVal = TESOCWaitUntilNotBusy(SOC_TESOC_BASE,
                                               TESOC_TIMEOUT_TEST_END);
                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC End DSP2 Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
                break;

            case TESOC_TEST_ID_ISSDSSVIP:
            case TESOC_TEST_ID_ISS:
            case TESOC_TEST_ID_DSS:
            case TESOC_TEST_ID_VIP:
                /* Power down ISS for TESOC to start test */
                retVal += PMHALStaticDepDisable(
                    PMHAL_PRCM_CD_IPU1,
                    PMHAL_PRCM_CD_ISS);
                retVal += PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_ISS,
                                                    &idleState);
                if (PM_SUCCESS == retVal)
                {
                    if (PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL == idleState)
                    {
                        PMHALModuleSIdleModeSet(
                            PMHAL_PRCM_MOD_ISS,
                            PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE,
                            PM_TIMEOUT_NOWAIT);
                    }
                }
                retVal = PMHALModuleStandbyStatusGet(PMHAL_PRCM_MOD_ISS,
                                                     &standbyState);
                if (PM_SUCCESS == retVal)
                {
                    if (PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL ==
                        standbyState)
                    {
                        PMHALModuleStandbyModeSet(
                            PMHAL_PRCM_MOD_ISS,
                            PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY,
                            PM_TIMEOUT_NOWAIT);
                    }
                }
                retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_ISS,
                                             PMHAL_PRCM_MODULE_MODE_DISABLED,
                                             PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMSetCdClockMode(
                    (pmhalPrcmCdId_t) PMHAL_PRCM_CD_ISS,
                    PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                    PM_TIMEOUT_NOWAIT);
                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to Power Down ISS, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
                retVal = PMHALPdmSetPDState(
                    PMHAL_PRCM_PD_ISS,
                    PMHAL_PRCM_PD_STATE_OFF,
                    PM_TIMEOUT_NOWAIT);

                /* Power down DSS for TESOC to start test */
                retVal += PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_DSS,
                                                    &idleState);
                if (PM_SUCCESS == retVal)
                {
                    if (PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL == idleState)
                    {
                        PMHALModuleSIdleModeSet(
                            PMHAL_PRCM_MOD_DSS,
                            PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE,
                            PM_TIMEOUT_NOWAIT);
                    }
                }
                retVal = PMHALModuleStandbyStatusGet(PMHAL_PRCM_MOD_DSS,
                                                     &standbyState);
                if (PM_SUCCESS == retVal)
                {
                    if (PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL ==
                        standbyState)
                    {
                        PMHALModuleStandbyModeSet(
                            PMHAL_PRCM_MOD_DSS,
                            PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY,
                            PM_TIMEOUT_NOWAIT);
                    }
                }
                /* Disable static dependency on DSS */
                retVal += PMHALStaticDepDisableAllSlaveDep(PMHAL_PRCM_CD_DSS);
                /* Change module mode and cut off clocks */
                retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_DSS,
                                             PMHAL_PRCM_MODULE_MODE_DISABLED,
                                             PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMSetCdClockMode(
                    (pmhalPrcmCdId_t) PMHAL_PRCM_CD_DSS,
                    PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                    PM_TIMEOUT_NOWAIT);
                /* Disable clock dependency of modules in DSS_CM_CORE domain */
                retVal += PMHALCMModuleClockDisable(
                    PMHAL_PRCM_MOD_DSS,
                    PMHAL_PRCM_CLK_HDMI_CEC_GFCLK,
                    PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMModuleClockDisable(
                    PMHAL_PRCM_MOD_DSS,
                    PMHAL_PRCM_CLK_HDMI_PHY_GFCLK,
                    PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMModuleClockDisable(
                    PMHAL_PRCM_MOD_DSS,
                    PMHAL_PRCM_CLK_DSS_GFCLK,
                    PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMModuleClockDisable(
                    PMHAL_PRCM_MOD_DSS,
                    PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK,
                    PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMModuleClockDisable(
                    PMHAL_PRCM_MOD_DSS,
                    PMHAL_PRCM_CLK_HDMI_DPLL_CLK,
                    PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMModuleClockDisable(
                    PMHAL_PRCM_MOD_DSS,
                    PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK,
                    PM_TIMEOUT_NOWAIT);
                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to Power Down DSS, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
                retVal += PMHALPdmSetPDState(
                    PMHAL_PRCM_PD_DSS,
                    PMHAL_PRCM_PD_STATE_OFF,
                    PM_TIMEOUT_NOWAIT);

                /*Power down VIP for TESOC to start test */
                retVal += PMHALModuleSIdleStatusGet(PMHAL_PRCM_MOD_VIP1,
                                                    &idleState);
                if (PM_SUCCESS == retVal)
                {
                    if (PMHAL_PRCM_MODULE_SIDLESTATE_FUNCTIONAL == idleState)
                    {
                        PMHALModuleSIdleModeSet(
                            PMHAL_PRCM_MOD_VIP1,
                            PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE,
                            PM_TIMEOUT_NOWAIT);
                    }
                }

                retVal = PMHALModuleStandbyStatusGet(PMHAL_PRCM_MOD_VIP1,
                                                     &standbyState);
                if (PM_SUCCESS == retVal)
                {
                    if (PMHAL_PRCM_MODULE_MSTANDBYSTATE_FUNCTIONAL ==
                        standbyState)
                    {
                        PMHALModuleStandbyModeSet(
                            PMHAL_PRCM_MOD_VIP1,
                            PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY,
                            PM_TIMEOUT_NOWAIT);
                    }
                }

                retVal += PMHALModuleModeSet(PMHAL_PRCM_MOD_VIP1,
                                             PMHAL_PRCM_MODULE_MODE_DISABLED,
                                             PM_TIMEOUT_NOWAIT);
                retVal += PMHALCMSetCdClockMode(
                    (pmhalPrcmCdId_t) PMHAL_PRCM_CD_CAM,
                    PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP,
                    PM_TIMEOUT_NOWAIT);
                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to Power Down VIP, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
                /* Power down modules after TESOC test */
                retVal += PMHALPdmSetPDState(
                    PMHAL_PRCM_PD_CAM,
                    PMHAL_PRCM_PD_STATE_OFF,
                    PM_TIMEOUT_NOWAIT);
                if (PM_SUCCESS != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n PRCM Failed to Disable ISS/DSS/VIP, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                if (TRUE == tesocTestConfig->completionIntrEnable)
                {
                    /* Configure TESOC Interrupt */
                    TESOCIntrEnable(SOC_TESOC_BASE,
                                    TESOC_INTR_FLAG_TEST_COMPLETION);
                }

                /* Clear TESOC status registers */
                retVal = TESOCClearPrevState(SOC_TESOC_BASE,
                                             tesocTestConfig->domainLabel);

                /* Configure TESOC and start the test */
                retVal += TESOCConfigAndStart(SOC_TESOC_BASE, tesocTestConfig);
                /* Wait for TESOC to start test */
                retVal += TESOCWaitUntilBusy(SOC_TESOC_BASE,
                                             TESOC_TIMEOUT_TEST_START);

                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC Start ISS/DSS/VIP Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }

                /* Wait for TESOC test to complete */
                retVal = TESOCWaitUntilNotBusy(SOC_TESOC_BASE,
                                               TESOC_TIMEOUT_TEST_END);
                if (STW_SOK != retVal)
                {
                    SBLLibPrintf(
                        SBLLIB_TRACE_LEVEL_ERROR,
                        "\n TESOC End ISS/DSS/VIP Configuration Failed, Aborting Boot\n");
                    SBLLibAbortBoot();
                }
                break;

            default:
                /* To remove MISRA C error */
                break;
        }
    }

    return retVal;
}

int32_t SBLLibCheckTesocTestResult(const tesocTestCfg_t *tesocTestConfig)
{
    /* Return  TESOC test results */
    return TESOCCheckTestResult(SOC_TESOC_BASE, tesocTestConfig);
}

int32_t SBLLibRegisterCRCCallback(SBLLibCalculateCRCFxn calculateCRCFxn)
{
    int32_t retVal = STW_SOK;
    if (calculateCRCFxn != NULL)
    {
        gCalculateCRCFxn = calculateCRCFxn;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

int32_t SBLLibRegisterAuthenticateRPRCCallback(
    SBLLibAuthenticateRPRCFxn authenticateRPRCFxn)
{
    int32_t retVal = STW_SOK;
    if (authenticateRPRCFxn != NULL)
    {
        gAuthenticateRPRCFxn = authenticateRPRCFxn;
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
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
        SblLibEVEMMUConfig(SBLLIB_SOC_IPU_EVE_MMU0_BASE, entryPoint);
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
        SblLibEVEMMUConfig(SBLLIB_SOC_IPU_EVE_MMU0_BASE,
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

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static inline void SblLibWaitForInterrupt(void)
{
    asm (" WFI");
}

static void SblLibSetIPUIdle(void)
{
    /*
     * PRCM Override should be removed to allow the IPU to go to low power
     * state.
     */
    HW_WR_FIELD32(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_IPU_WAKEUP,
                  CTRL_CORE_SEC_IPU_WAKEUP_WKUP_EN,
                  0x00);

    /* Set IPU in deep sleep to set CM standby */
    HW_WR_FIELD32(SOC_IPU1_C0_INTC_BASE + IPU_M4_NVIC_SYSTEM_CONTROL,
                  IPU_M4_NVIC_SYSTEM_CONTROL_SLEEPDEEP,
                  0x01);

    HW_WR_FIELD32(SOC_IPU1_MMU_BASE + IPU_MMU_SYSCONFIG,
                  IPU_MMU_SYSCONFIG_IDLEMODE,
                  IPU_MMU_SYSCONFIG_IDLEMODE_SSIDLE);

    /* Set StandBy Core Sysconfig  */
    HW_WR_FIELD32(SOC_IPU1_WUGEN_BASE + IPU_STANDBY_CORE_SYSCONFIG,
                  IPU_STANDBY_CORE_SYSCONFIG_STANDBYMODE,
                  0x3);

    /* Set Idle Core Sysconfig */
    HW_WR_FIELD32(SOC_IPU1_WUGEN_BASE + IPU_IDLE_CORE_SYSCONFIG,
                  IPU_IDLE_CORE_SYSCONFIG_IDLEMODE,
                  0x3);
}

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

