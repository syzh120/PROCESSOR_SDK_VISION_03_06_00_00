/*
 *  Copyright (c) Texas Instruments Incorporated 2013-2016
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

/*-----------------------------------------------------------------------*/
/*fatlib                                                   */
/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

/*
 * This file was modified from a sample available from the FatFs
 * web site. It was modified to work with the SitaraWare USB stack.
 */
#include <string.h>
#include <stdint.h>
#include <diskio.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/fatlib/mmcsd_proto.h>
#include <ti/drv/stw_lld/fatlib/hs_mmcsdlib.h>
#include <ti/drv/stw_lld/fatlib/fatfs/ff.h>
#include <ti/drv/stw_lld/fatlib/hsmmcsd_edma.h>

typedef struct _fatDevice
{
    /* Pointer to underlying device/controller */
    void        *dev;

    /* File system pointer */
    FATFS       *fs;

    /* state */
    uint32_t initDone;
}fatDevice;

#define DRIVE_NUM_MMCSD     0
#define DRIVE_NUM_MAX      2

fatDevice fat_devices[DRIVE_NUM_MAX] = {{NULL, NULL, 0, }, {NULL, NULL, 0, }};

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS
disk_initialize(
    BYTE bValue)                /* Physical drive number (0) */
{
    uint32_t status;

    if (DRIVE_NUM_MAX <= bValue)
    {
        return STA_NODISK;
    }

    if ((DRIVE_NUM_MMCSD == bValue) && (fat_devices[bValue].initDone != 1))
    {
        mmcsdCardInfo *card = (mmcsdCardInfo *) fat_devices[bValue].dev;

        /* SD Card init */
        status = MMCSDCardInit(card->ctrl);

        if (status == 0)
        {
            HSMMCSDUartPuts("\r\nCard Init Failed \r\n");
            return STA_NOINIT;
        }
        else
        {
            if (card->cardType == MMCSD_CARD_SD)
            {
                HSMMCSDUartPuts("\r\nSD Card ");
                HSMMCSDUartPuts("version : ");
                HSMMCSDUARTPutNum(card->sd_ver);

                if (card->highCap)
                {
                    HSMMCSDUartPuts(", High Capacity");
                }

                if (card->tranSpeed == SD_TRANSPEED_50MBPS)
                {
                    HSMMCSDUartPuts(", High Speed");
                }
            }
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
            else if (card->cardType == MMCSD_CARD_MMC)
            {
                HSMMCSDUartPuts("\r\nMMC Card ");
            }
#endif
            else
            {
                /* MISRA C compliant */
                HSMMCSDUartPuts("\r\nUnknown Card Type...");

            }

            /*set the block size*/
            // MMCSDBlockSizeSet(card->ctrl);

            /* Set bus width */
            if (card->cardType == MMCSD_CARD_SD)
            {
                MMCSDBusWidthSet(card->ctrl);
            }

            /* Transfer speed */
            MMCSDTranSpeedSet(card->ctrl);
        }

        fat_devices[bValue].initDone = 1;
    }

    return 0;
}

/*-----------------------------------------------------------------------*/
/* Returns the current status of a drive                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(
    BYTE drv)                   /* Physical drive number (0) */
{
    return 0;
}

/*-----------------------------------------------------------------------*/
/* This function reads sector(s) from the disk drive                     */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(
    BYTE  pdrv,              /* Physical drive number (0) */
    BYTE *buff,             /* Pointer to the data buffer to store read data */
    DWORD sector,           /* Physical drive nmuber (0) */
    UINT  count)            /* Sector count (1..255) */
{
    if (pdrv == DRIVE_NUM_MMCSD)
    {
        mmcsdCardInfo *card = (mmcsdCardInfo *) fat_devices[pdrv].dev;

        if (MMCSDReadCmdSend(card->ctrl, buff, sector, count) == 1)
        {
            return RES_OK;
        }
    }

    return RES_ERROR;
}

/*-----------------------------------------------------------------------*/
/* This function writes sector(s) to the disk drive                     */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
DRESULT disk_write(
    BYTE        pdrv,    /* Physical drive number (0) */
    const BYTE *buff,       /* Pointer to the data to be written */
    DWORD       sector,     /* Start sector number (LBA) */
    UINT        count)      /* Sector count (1..255) */
{
    if (pdrv == DRIVE_NUM_MMCSD)
    {
        mmcsdCardInfo *card = (mmcsdCardInfo *) fat_devices[pdrv].dev;
        /* WRITE BLOCK */
        if (MMCSDWriteCmdSend(card->ctrl, (BYTE *) buff, sector, count) == 1)
        {
            return RES_OK;
        }
    }

    return RES_ERROR;
}

#endif /* _READONLY */

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl(
    BYTE  drv,              /* Physical drive number (0) */
    BYTE  ctrl,             /* Control code */
    void *buff)             /* Buffer to send/receive control data */
{
    DRESULT result = RES_OK;

    switch (ctrl) {
        case CTRL_SYNC:
            break;

        case GET_SECTOR_SIZE:
            if (drv == DRIVE_NUM_MMCSD)
            {
                mmcsdCardInfo *card = (mmcsdCardInfo *) fat_devices[drv].dev;
                /* READ SECTOR SIZE*/
                *(WORD *)buff = card->blkLen;
            }
            break;

        /* Other commands are not implemented because they are not needed given the chosen configuration
           from ffconf.h (see definitions of these commands in diskio.h).  If the configuration changes
           such that the commands are needed, then support should be added to this function */
        default:
            result = RES_PARERR;
            break;
    }

    return (result);
}

/*---------------------------------------------------------*/
/* User Provided Timer Function for FatFs module           */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support a real time clock.          */

DWORD get_fattime(void)
{
    return ((2007UL - 1980) << 25)  // Year = 2007
           | (6UL << 21)            // Month = June
           | (5UL << 16)            // Day = 5
           | (11U << 11)            // Hour = 11
           | (38U << 5)             // Min = 38
           | (0U >> 1)              // Sec = 0
    ;
}

void mem_cpy_dma (void* dst, const void* src, uint32_t cnt)
{
    /* Hard-coding the index into fat_devices to '0' since this has nothing to do with actual fat device, so take first */
    mmcsdCardInfo *card = (mmcsdCardInfo *) fat_devices[0].dev;
    MMCSDMemCopy(card->ctrl, dst, src, cnt);
}
