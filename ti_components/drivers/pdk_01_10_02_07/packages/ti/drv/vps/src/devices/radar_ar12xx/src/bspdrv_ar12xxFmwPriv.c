/*
 *   Copyright (c) Texas Instruments Incorporated 2017-2018
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
 */

/**
 *  \file bspdrv_ar12xxFmwPriv.c
 *
 *  \brief  This file contains function definitions used privately by the
 *          AR12xx Radar sensor driver for firmware download and flashing.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <bspdrv_ar12xxPriv.h>
/* ES1.0 Firmware */
#include <1.0/xwr12xx_masterss.h>
#include <1.0/xwr12xx_xwr14xx_radarss.h>
/* ES2.0 Firmware */
#include <2.0/xwr12xx_masterss.h>
#include <2.0/xwr12xx_xwr14xx_radarss.h>
#include <xwr1xxx_config.h>
/* ES3.0 Meta Image */
#include <xwr12xx_metaImage.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** Firmware is prefixed with the file type and length. Hence 2*4 bytes
 *  are padded at the beginning of the firmware.
 */
#define BSP_AR12XX_FMW_PREFIX_SIZE       (8U)

/** Firmware download chunk size */
#define BSP_AR12XX_FMW_CHUNK_SIZE        (232U)

/** Radar Communication Timeout */
#define BSP_AR12XX_RADAR_COMM_TIMEOUT    (1000U)

/** AR12xx boot mode Opcode for Ping */
#define BSP_AR12XX_FMW_FLASHLDR_PING              (0x20U)
/** AR12xx boot mode Opcode to Start download */
#define BSP_AR12XX_FMW_FLASHLDR_START_DOWNLOAD    (0x21U)
/** AR12xx boot mode Opcode for file close */
#define BSP_AR12XX_FMW_FLASHLDR_FILE_CLOSE        (0x22U)
/** AR12xx boot mode Opcode for getting the last status */
#define BSP_AR12XX_FMW_FLASHLDR_GET_LAST_STATUS   (0x23U)
/** AR12xx boot mode Opcode for sending data */
#define BSP_AR12XX_FMW_FLASHLDR_SEND_DATA         (0x24U)
/** AR12xx boot mode Opcode to disconnect */
#define BSP_AR12XX_FMW_FLASHLDR_DISCONNECT        (0x26U)
/** AR12xx boot mode Opcode to erase */
#define BSP_AR12XX_FMW_FLASHLDR_ERASE             (0x28U)
/** AR12xx boot mode Opcode to erase the file */
#define BSP_AR12XX_FMW_FLASHLDR_FILE_ERASE        (0x2EU)
/** AR12xx boot mode Opcode to get the version of the firmware */
#define BSP_AR12XX_FMW_FLASHLDR_GET_VERSION_INFO  (0x2FU)

/** Flash type understood by the AR12xx ROM */
#define BSP_AR12XX_FMW_FLASH_TYPE                 (0x2U)

/** Erase Message Size */
#define BSP_AR12XX_FMW_ERASE_MSG_SIZE \
    (sizeof (UInt8) + 3 * sizeof (UInt32))

/** Default Firmware transfer chunk size */
#define BSP_AR12XX_FMW_DEFAULT_CHUNK_SIZE          (240U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * \brief   AR12XX Section Type Names.
 */
static const char *gBspSectionNames[] =
{
    "BSS_BUILD",
    "CALIB_DATA",
    "CONFIG_INFO",
    "MSS_BUILD",
    "META_IMAGE"
};

/* Message Buffer to write when erasing UART flash */
#ifndef __cplusplus
#pragma DATA_ALIGN(gUartEraseMsgBuffer, 128);
#else
#pragma DATA_ALIGN(128);
#endif
static UInt32      gUartEraseMsgBuffer[] =
{
    BSP_AR12XX_FMW_FLASHLDR_ERASE, BSP_AR12XX_FMW_FLASH_TYPE, 0U, 0U
};

/* Buffer to hold the firmware in chunks */
#ifndef __cplusplus
#pragma DATA_ALIGN(gUartChunkBuffer, 128);
#else
#pragma DATA_ALIGN(128);
#endif
static UInt8       gUartChunkBuffer[BSP_AR12XX_FMW_DEFAULT_CHUNK_SIZE + 1U];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief  Function to download the section of the firmware as given by the
 *          fileType.
 *
 *  \param  sectionType     File/Section type. Refer to
 *                          #Bsp_a12xxSectionDwldType for valid values.
 *
 *  \return retVal          BSP_OK if the firmware section is downloaded
 *                          successfully. BSP_EFAIL otherwise.
 */
static Int32 Bsp_ar12xxFmwSectionDwld(UInt32 sectionType);

/**
 *  \brief  Function to download the chunks of the firmware. Wrapper to the
 *          radar interface APIs.
 *
 *  \param  remChunks       Number of chunks of the firmware left to be
 *                          downloaded.
 *  \param  chunkLen        Chunk length of the current chunk being downloaded.
 *  \param  chunk           Pointer to the chunk being downloaded.
 *
 *  \return retVal          BSP_OK if the firmware chunk is downloaded
 *                          successfully. BSP_EFAIL otherwise.
 */
static Int32 Bsp_ar12xxFmwChunkDwld(UInt32 remChunks, UInt32 chunkLen,
                                    const UInt8 *chunk);

/**
 *  \brief  Function to get the firmware buffer and length
 *          based on the section type and the AR12 silicon version.
 *
 *  \param  sectionType     Type of the section to be loaded.
 *  \param  pImgBuffer      Pointer to the firmware which is populated
 *                          by the API.
 *  \param  imgLen          Pointer to the firmware section length populated
 *                          by the API.
 *
 *  \return retVal  BSP_OK if the BPM chirp is configured.
 */
static Int32 Bsp_ar12xxFmwGetBuffers(UInt32  sectionType,
                                     UInt8 **pImgBuffer,
                                     UInt32 *imgLen);

/** \brief Function to send the firmware chunk by chunk to the AR12xx.
 *
 *  \param  deviceId    Device Index of the AR12 device.
 *  \param  pObj        Pointer to the BSP AR12 object.
 *  \param  pImgBuffer  Image buffer for the firmware section.
 *  \param  length      Length of the full firmware section.
 *
 *  \return retVal  BSP_SOK - If the transmit of the start dowload is successful
 *                  BSP_EFAIL - Otherwise.
 */
static Int32 Bsp_ar12xxFmwSendSectionToFlash(UInt32 deviceId,
                                             Bsp_ar12xxObj *pObj,
                                             const UInt8   *pImgBuffer,
                                             UInt32         length);

/** \brief Function to send the firmware chunk to the AR12xx.
 *
 *  \param  deviceId    Device Index of the AR12 device.
 *  \param  pObj        Pointer to the BSP AR12 object.
 *  \param  pImgBuffer  Image buffer for the firmware section.
 *  \param  length      Length of the full firmware section.
 *
 *  \return retVal  BSP_SOK - If the transmit of the start dowload is successful
 *                  BSP_EFAIL - Otherwise.
 */
static Int32 Bsp_ar12xxFmwSendChunkToFlash(UInt32 deviceId,
                                           Bsp_ar12xxObj *pObj,
                                           const UInt8   *pImgBuffer,
                                           UInt32         length);

/** \brief Function to close the flashing of a given section.
 *
 *  \param  deviceId    Device Index of the AR12 device.
 *  \param  pObj        Pointer to the BSP AR12 object.
 *  \param  sectionType Section type to start flashing. For valid values
 *                      refer #Bsp_a12xxSectionDwldType.
 *
 *  \return retVal  BSP_SOK - If the close of the section is complete.
 *                  BSP_EFAIL - Otherwise.
 */
static Int32 Bsp_ar12xxFmwSendSectionToFlashClose(UInt32 deviceId,
                                                  Bsp_ar12xxObj *pObj,
                                                  UInt32         sectionType);

/** \brief Function to send the start download sequence for the firmware
 *         sections.
 *
 *  \param  deviceId    Device Index of the AR12 device.
 *  \param  pObj        Pointer to the BSP AR12 object.
 *  \param  sectionType Section type to start flashing. For valid values
 *                      refer #Bsp_a12xxSectionDwldType.
 *  \param  sectionSize Size of the section to be flashed.
 *
 *  \return retVal  BSP_SOK - If the transmit of the start dowload is successful
 *                  BSP_EFAIL - Otherwise.
 */
static Int32 Bsp_ar12xxFmwStartFlashDwnld(UInt32 deviceId,
                                          Bsp_ar12xxObj *pObj,
                                          UInt32         sectionType,
                                          UInt32         sectionSize);

/** \brief Function to read the status of the last packet.
 *
 *  \param  deviceId    Device Index of the AR12 device.
 *  \param  pObj        Pointer to the BSP AR12 object.
 *
 *  \return retVal  BSP_SOK - If the transmit of the start dowload is successful
 *                  BSP_EFAIL - Otherwise.
 */
static Int32 Bsp_ar12xxFmwFlashReadLastStatus(UInt32 deviceId,
                                              Bsp_ar12xxObj *pObj);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 Bsp_ar12xxFmwSpiDwld(void)
{
    Int32 retVal = BSP_SOK;
    UInt32 arDevRev = gBspAr12xxObj.arDeviceRevision;
    if((arDevRev == 1U) || (arDevRev == 2U))
    {
        retVal = Bsp_ar12xxFmwSectionDwld(BSP_AR12XX_SECTIONTYPE_MSS_BUILD);

        if (retVal == BSP_SOK)
        {
            retVal = Bsp_ar12xxFmwSectionDwld(BSP_AR12XX_SECTIONTYPE_BSS_BUILD);
        }
        if (retVal == BSP_SOK)
        {
            gBspAr12xxObj.radarInitCompleteFlag = 0U;
            rlDeviceConfigureAckTimeout(0U);
            retVal = Bsp_ar12xxFmwSectionDwld(BSP_AR12XX_SECTIONTYPE_CONFIG_INFO);
        }
    }
    else
    {
        /* Download Meta Image if device is ES 3.0 AR1243 */
        retVal = Bsp_ar12xxFmwSectionDwld(BSP_AR12XX_SECTIONTYPE_META_IMAGE);
    }
    return retVal;
}

Int32 Bsp_ar12xxFmwRun(void)
{
    Int32  retVal = BSP_SOK;
    UInt32 numToWait = Bsp_ar12xxCountBits(gBspAr12xxObj.devIdxMap);
    /* Set a sleep time of 10 seconds for the AR12xx device boot time. This
     * is kept at a worst possible maximum time.
     */
    UInt32 timeout = BSP_AR12XX_TIMEOUT_MAX;
    UInt32 arDevRev = gBspAr12xxObj.arDeviceRevision;

    /* Wait for initialization to complete */
    rlDeviceConfigureAckTimeout(BSP_AR12XX_RADAR_COMM_TIMEOUT);
    if((arDevRev == 1U) || (arDevRev == 2U))
    {
        while ((gBspAr12xxObj.radarInitCompleteFlag != numToWait)
                && (timeout != 0U))
        {
            BspOsal_sleep(1U);
            timeout--;
        }
        if (gBspAr12xxObj.radarInitCompleteFlag != numToWait)
        {
            retVal = BSP_EFAIL;
        }
    }
    if (retVal == BSP_SOK)
    {
        /* Run the firmware */
        timeout = BSP_AR12XX_TIMEOUT_MAX;
        BspOsal_sleep(20U);
        gBspAr12xxObj.radarDevStartCompleteFlag = 0U;
        retVal = rlDeviceRfStart(gBspAr12xxObj.devIdxMap);

        if (retVal == BSP_SOK)
        {
            /* Wait for the radar firmware to run */
            while ((gBspAr12xxObj.radarDevStartCompleteFlag != numToWait) &&
                   (timeout != 0U))
            {
                BspOsal_sleep(1U);
                timeout--;
            }
            if (gBspAr12xxObj.radarDevStartCompleteFlag != numToWait)
            {
                retVal = BSP_EFAIL;
            }
        }
    }
    return retVal;
}

Int32 Bsp_ar12xxFmwEraseFlash(UInt32 device, Bsp_ar12xxObj *pObj)
{
    Int32  status       = BSP_SOK;
    UInt32 packetLength = (UInt32) BSP_AR12XX_FMW_ERASE_MSG_SIZE;

    /* Workaround for not flushing. Read Extra ACK. */
    status = Bsp_ar12xxUartReadAck(device, pObj);
    if (status == BSP_SOK)
    {
        BspOsal_sleep(100U);
        status = Bsp_ar12xxUartSendPacket(device, pObj,
                                          (UInt8 *) gUartEraseMsgBuffer,
                                          packetLength);
    }
    if (status == BSP_SOK)
    {
        BspOsal_sleep(100U);
        status = Bsp_ar12xxUartReadAck(device, pObj);
    }
    return status;
}

Int32 Bsp_ar12xxFmwSectionFlash(UInt32 deviceId, Bsp_ar12xxObj *pObj, UInt32 sectionType)
{
    Int32  retVal      = BSP_SOK;
    UInt32 sectionSize = 0U;
    UInt8 *pImgBuffer  = NULL;

    retVal = Bsp_ar12xxFmwGetBuffers(sectionType, &pImgBuffer,
                                     &sectionSize);

    if (retVal == BSP_SOK)
    {
        retVal = Bsp_ar12xxFmwStartFlashDwnld(deviceId,
                                              pObj, sectionType, sectionSize);
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_ar12xxFmwSendSectionToFlash(deviceId,
                                                 pObj, pImgBuffer, sectionSize);
    }
    if (retVal == BSP_SOK)
    {
        retVal = Bsp_ar12xxFmwSendSectionToFlashClose(deviceId,
                                                      pObj, sectionType);
    }
    return retVal;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */

static Int32 Bsp_ar12xxFmwSectionDwld(UInt32 sectionType)
{
    Int32  retVal = BSP_SOK;
    UInt32 imgLen;
    UInt32 firstChunk[BSP_AR12XX_FMW_CHUNK_SIZE / 4U];
    UInt8 *pImgBuffer     = NULL;
    UInt32 usLastChunkLen = 0, usFirstChunkLen = 0, iNumChunks = 0;

    retVal = Bsp_ar12xxFmwGetBuffers(sectionType, &pImgBuffer, &imgLen);

    if (retVal == BSP_SOK)
    {
        /* Download the firmware to the device.
         * The first chunk is prefixed with the file type and the imagesize
         * length. Hence 8 is added to the total image length.
         */
        iNumChunks = (imgLen + 8U) / BSP_AR12XX_FMW_CHUNK_SIZE;
        /* If there is only one chunk then the length of the first chunk is
         * made the image length + 8. Else the chunk lengths are calculated
         * and the last chunk remaining bytes length is calculated.
         */
        if (iNumChunks > 0U)
        {
            usLastChunkLen  = (imgLen + 8U) % BSP_AR12XX_FMW_CHUNK_SIZE;
            usFirstChunkLen = BSP_AR12XX_FMW_CHUNK_SIZE;
        }
        else
        {
            usFirstChunkLen = imgLen + 8U;
        }
        firstChunk[0] = sectionType;
        firstChunk[1] = imgLen;
        memcpy((void *) &firstChunk[2], (void *) pImgBuffer,
               usFirstChunkLen - 8U);

        BspOsal_printf(" AR12XX: Firmware Download Started : Ftype: %s\n\r",
                       gBspSectionNames[sectionType]);
        retVal = Bsp_ar12xxFmwChunkDwld(iNumChunks,
                                        usFirstChunkLen,
                                        (UInt8 *) firstChunk);
        if (retVal != BSP_SOK)
        {
            BspOsal_printf(
                " AR12XX: Firmware first chunk download Failed : Ftype: %s\n\r",
                gBspSectionNames[sectionType]);
        }
    }
    if ((retVal == BSP_SOK) && (iNumChunks > 0U))
    {
        UInt32 totalNumChunks = iNumChunks + 1U;

        pImgBuffer = (UInt8 *) (pImgBuffer +
                                (BSP_AR12XX_FMW_CHUNK_SIZE -
                                 BSP_AR12XX_FMW_PREFIX_SIZE));
        iNumChunks--;

        /* Repeat firmware load for the rest of the chunks */
        while (iNumChunks > 0U)
        {
            retVal =
                Bsp_ar12xxFmwChunkDwld(iNumChunks, BSP_AR12XX_FMW_CHUNK_SIZE,
                                       pImgBuffer);

            if (retVal != BSP_SOK)
            {
                BspOsal_printf(
                    " AR12XX: Firmware chunk No. %d download Failed : Ftype: %s\n\r",
                    (totalNumChunks - iNumChunks),
                    gBspSectionNames[sectionType]);
                break;
            }
            pImgBuffer = (UInt8 *) (pImgBuffer +
                                    BSP_AR12XX_FMW_CHUNK_SIZE);
            iNumChunks--;
        }
    }
    if ((retVal == BSP_SOK) && (usLastChunkLen > 0U))
    {
        retVal = Bsp_ar12xxFmwChunkDwld(0, usLastChunkLen, pImgBuffer);
        if (retVal < 0)
        {
            BspOsal_printf(
                " AR12XX: Firmware last chunk download Failed : Ftype: %s\n\r",
                gBspSectionNames[sectionType]);
        }
    }
    if (retVal == BSP_SOK)
    {
        BspOsal_printf(
            " AR12XX: Firmware Download Successful : Ftype: %s\n\r",
            gBspSectionNames[sectionType]);
    }
    return retVal;
}

static Int32 Bsp_ar12xxFmwChunkDwld(UInt32 remChunks, UInt32 chunkLen,
                                    const UInt8 *chunk)
{
    Int32        retVal    = BSP_EFAIL;
    rlFileData_t fileChunk = {0U};
    fileChunk.chunkLen = chunkLen;
    memcpy((void *) fileChunk.fData, (const void *) chunk, chunkLen);

    retVal = (Int32) rlDeviceFileDownload(gBspAr12xxObj.devIdxMap,
                                          &fileChunk, (UInt16) remChunks);
    return retVal;
}

static Int32 Bsp_ar12xxFmwGetBuffers(UInt32 sectionType, UInt8 **pImgBuffer,
                                     UInt32 *imgLen)
{
    Int32  retVal   = BSP_SOK;
    UInt32 arDevRev = gBspAr12xxObj.arDeviceRevision;

    if (arDevRev == 1U)
    {
        /* For ES1.0 AR1243 */
        if (sectionType == (UInt32) BSP_AR12XX_SECTIONTYPE_BSS_BUILD)
        {
            *pImgBuffer = (UInt8 *) &bssImg_1_0[0];
            *imgLen     = sizeof (bssImg);
        }
        else if (sectionType == (UInt32) BSP_AR12XX_SECTIONTYPE_MSS_BUILD)
        {
            *pImgBuffer = (UInt8 *) &mssImg_1_0[0];
            *imgLen     = sizeof (mssImg);
        }
        else if (sectionType == (UInt32) BSP_AR12XX_SECTIONTYPE_CONFIG_INFO)
        {
            *pImgBuffer = (UInt8 *) &configImg[0];
            *imgLen     = sizeof (configImg);
        }
        else
        {
            /* Any other file type currently not supported */
            retVal = BSP_EFAIL;
        }
    }
    else if(arDevRev == 2U)
    {
        /* For ES2.0 AR1243 */
        if (sectionType == (UInt32) BSP_AR12XX_SECTIONTYPE_BSS_BUILD)
        {
            *pImgBuffer = (UInt8 *) bssImg;
            *imgLen     = sizeof (bssImg);
        }
        else if (sectionType == (UInt32) BSP_AR12XX_SECTIONTYPE_MSS_BUILD)
        {
            *pImgBuffer = (UInt8 *) mssImg;
            *imgLen     = sizeof (mssImg);
        }
        else if (sectionType == (UInt32) BSP_AR12XX_SECTIONTYPE_CONFIG_INFO)
        {
            *pImgBuffer = (UInt8 *) &configImg[0];
            *imgLen     = sizeof (configImg);
        }
        else
        {
            /* Any other file type currently not supported */
            retVal = BSP_EFAIL;
        }
    }
    else
    {
        /* For ES3.0 AR1243 */
        if (sectionType == (UInt32) BSP_AR12XX_SECTIONTYPE_META_IMAGE)
        {
            *pImgBuffer = (UInt8 *) metaImage;
            *imgLen     = sizeof (metaImage);
        }
        else
        {
            /* Any other file type currently not supported */
            retVal = BSP_EFAIL;
        }
    }
    return retVal;
}

static Int32 Bsp_ar12xxFmwSendSectionToFlash(UInt32 deviceId,
                                             Bsp_ar12xxObj *pObj,
                                             const UInt8   *pImgBuffer,
                                             UInt32         length)
{
    Int32  retVal = BSP_SOK;
    UInt32 offset = 0U, chunkSize = 0U;
    /* Send the firmware to the AR12 ROM chunk by chunk */
    while (offset < length)
    {
        if ((offset + BSP_AR12XX_FMW_DEFAULT_CHUNK_SIZE) <= length)
        {
            chunkSize = BSP_AR12XX_FMW_DEFAULT_CHUNK_SIZE;
        }
        else
        {
            chunkSize = length - offset;
        }
        retVal = Bsp_ar12xxFmwSendChunkToFlash(deviceId, pObj,
                                               &pImgBuffer[offset],
                                               chunkSize);
        if (BSP_SOK != retVal)
        {
            break;
        }
        offset += chunkSize;
    }
    return retVal;
}

static Int32 Bsp_ar12xxFmwSendChunkToFlash(UInt32 deviceId,
                                           Bsp_ar12xxObj *pObj,
                                           const UInt8   *pImgBuffer,
                                           UInt32         length)
{
    Int32 status = BSP_SOK;
    /* Create the chunk buffer with the chunk and the header */
    gUartChunkBuffer[0U] = BSP_AR12XX_FMW_FLASHLDR_SEND_DATA;
    memcpy(&gUartChunkBuffer[1U], pImgBuffer, length);

    status = Bsp_ar12xxUartSendPacket(deviceId,
                                      pObj, gUartChunkBuffer, length + 1U);
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxUartReadAck(deviceId, pObj);
    }
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxFmwFlashReadLastStatus(deviceId, pObj);
    }
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxUartRecvPacket(deviceId, pObj, sizeof (UInt8));
    }
    return status;
}

static Int32 Bsp_ar12xxFmwSendSectionToFlashClose(UInt32 deviceId,
                                                  Bsp_ar12xxObj *pObj,
                                                  UInt32         sectionType)
{
    Int32  status   = BSP_SOK;
    UInt32 totalLen = 0U;
    /* Prepare the packet for section close */
    gUartChunkBuffer[0U] = (UInt8) BSP_AR12XX_FMW_FLASHLDR_FILE_CLOSE;
    totalLen = totalLen + sizeof (UInt8);

    gUartChunkBuffer[1U] = (UInt8) ((sectionType & 0xFF000000U) >> 24U);
    gUartChunkBuffer[2U] = (UInt8) ((sectionType & 0x00FF0000U) >> 16U);
    gUartChunkBuffer[3U] = (UInt8) ((sectionType & 0x0000FF00U) >> 8U);
    gUartChunkBuffer[4U] = (UInt8) (sectionType & 0x000000FFU);
    totalLen += sizeof (UInt32);
    /* Send the packet and wait for acknowledge */
    status = Bsp_ar12xxUartSendPacket(deviceId, pObj,
                                      gUartChunkBuffer, totalLen);
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxUartReadAck(deviceId, pObj);
    }
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxFmwFlashReadLastStatus(deviceId, pObj);
    }
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxUartRecvPacket(deviceId, pObj, sizeof (UInt8));
    }
    return status;
}

static Int32 Bsp_ar12xxFmwStartFlashDwnld(UInt32 deviceId,
                                          Bsp_ar12xxObj *pObj,
                                          UInt32         sectionType,
                                          UInt32         sectionSize)
{
    UInt32 totalLen = 0U;
    Int32  status   = BSP_SOK;
    UInt32 storageType, mirrorEnabled;

    /* Create the Message for the start download. Protocol is based on
     * what the AR12 ROM can understand.
     */
    gUartChunkBuffer[0U] = BSP_AR12XX_FMW_FLASHLDR_START_DOWNLOAD;
    totalLen += sizeof (UInt8);

    gUartChunkBuffer[1U] = (UInt8) ((sectionSize & 0xFF000000U) >> 24U);
    gUartChunkBuffer[2U] = (UInt8) ((sectionSize & 0x00FF0000U) >> 16U);
    gUartChunkBuffer[3U] = (UInt8) ((sectionSize & 0x0000FF00U) >> 8U);
    gUartChunkBuffer[4U] = (UInt8) (sectionSize & 0x000000FFU);
    totalLen += sizeof (UInt32);

    storageType          = BSP_AR12XX_FMW_FLASH_TYPE;
    gUartChunkBuffer[5U] = (UInt8) ((storageType & 0xFF000000U) >> 24U);
    gUartChunkBuffer[6U] = (UInt8) ((storageType & 0x00FF0000U) >> 16U);
    gUartChunkBuffer[7U] = (UInt8) ((storageType & 0x0000FF00U) >> 8U);
    gUartChunkBuffer[8U] = (UInt8) (storageType & 0x000000FFU);
    totalLen += sizeof (UInt32);

    gUartChunkBuffer[9U]  = (UInt8) ((sectionType & 0xFF000000U) >> 24U);
    gUartChunkBuffer[10U] = (UInt8) ((sectionType & 0x00FF0000U) >> 16U);
    gUartChunkBuffer[11U] = (UInt8) ((sectionType & 0x0000FF00U) >> 8U);
    gUartChunkBuffer[12U] = (UInt8) (sectionType & 0x000000FFU);
    totalLen += sizeof (UInt32);

    mirrorEnabled         = 0U; /* Flag set to 0 for mirroring to be enabled */
    gUartChunkBuffer[13U] = (UInt8) ((mirrorEnabled & 0xFF000000U) >> 24U);
    gUartChunkBuffer[14U] = (UInt8) ((mirrorEnabled & 0x00FF0000U) >> 16U);
    gUartChunkBuffer[15U] = (UInt8) ((mirrorEnabled & 0x0000FF00U) >> 8U);
    gUartChunkBuffer[16U] = (UInt8) (mirrorEnabled & 0x000000FFU);
    totalLen += sizeof (UInt32);

    /* Workaround for not flushing. Read Extra ACK. */
    if (sectionType == BSP_AR12XX_SECTIONTYPE_BSS_BUILD)
    {
        status = Bsp_ar12xxUartReadAck(deviceId, pObj);
    }
    /* Send the Start download packet */
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxUartSendPacket(deviceId,
                                          pObj, gUartChunkBuffer, totalLen);
    }
    /* Wait for ack from AR12 */
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxUartReadAck(deviceId, pObj);
    }
    /* Ensure the packet is recieved correctly */
    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxFmwFlashReadLastStatus(deviceId, pObj);
    }

    if (status == BSP_SOK)
    {
        status = Bsp_ar12xxUartRecvPacket(deviceId, pObj, sizeof (UInt8));
    }
    return status;
}

static Int32 Bsp_ar12xxFmwFlashReadLastStatus(UInt32 deviceId,
                                              Bsp_ar12xxObj *pObj)
{
    Int32 status = BSP_SOK;
    gUartChunkBuffer[0U] = BSP_AR12XX_FMW_FLASHLDR_GET_LAST_STATUS;
    status = Bsp_ar12xxUartSendPacket(deviceId, pObj, gUartChunkBuffer, 1U);
    return status;
}

