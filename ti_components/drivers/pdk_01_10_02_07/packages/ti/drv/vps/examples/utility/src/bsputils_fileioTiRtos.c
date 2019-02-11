/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file bsputils_fileioTiRtos.c
 *
 *  \brief This file implements helper functions for accessing the sd card on
 *  top of TI RTOS MMCSD/FATFS driver.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#if defined (BARE_METAL)
#include <ti/csl/tistdtypes.h>
#else
#include <xdc/std.h>
#endif

#include <ti/csl/soc.h>
#include <ti/drv/vps/include/common/bsp_types.h>
#include <ti/drv/vps/include/common/trace.h>
#include <ti/drv/vps/include/common/bsp_config.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/drv/vps/include/common/bsp_common.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/include/boards/bsp_board.h>
#include <ti/drv/vps/include/devices/bsp_device.h>
#include <ti/drv/vps/examples/utility/bsputils_app.h>
#include <ti/drv/mmcsd/MMCSD.h>
#include <ti/drv/mmcsd/src/MMCSD_osal.h>
#include <ti/drv/mmcsd/soc/MMCSD_soc.h>
#include <ti/fs/fatfs/diskio.h>
#include <ti/fs/fatfs/FATFS.h>
#include <ti/fs/fatfs/ff.h>

#if defined(BARE_METAL)
/* No EDMA support for bare metal cases */
#else
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/sdo/edma3/drv/sample/bios6_edma3_drv_sample.h>
#endif
#include <ti/drv/vps/examples/utility/bsputils_fileio.h>


/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

typedef struct
{
    BspOsal_SemHandle edmaDone;
#if !defined(BARE_METAL)
    EDMA3_DRV_Handle  hEdma;
#endif
    Bool              sdInitDone;
    Bool              sdCardNotPresent;
    FATFS_Handle      fatfsHandle;
} SdFileSys_Obj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

  /* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static SdFileSys_Obj gSdFileSysObj = {0};

/* MMCSD function table for MMCSD implementation */
FATFS_DrvFxnTable FATFS_drvFxnTable = {
    MMCSD_close,
    MMCSD_control,
    MMCSD_init,
    MMCSD_open,
    MMCSD_write,
    MMCSD_read
};

/* FATFS configuration structure */
FATFS_HwAttrs FATFS_initCfg[_VOLUMES] =
{
    {
        0U
    },
    {
        1U
    },
    {
        2U
    },
    {
        3U
    }
};

/* FATFS objects */
FATFS_Object FATFS_objects[_VOLUMES];

/* FATFS configuration structure */
const FATFS_Config FATFS_config[_VOLUMES + 1] = {
    {
        &FATFS_drvFxnTable,
        &FATFS_objects[0],
        &FATFS_initCfg[0]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[1],
         &FATFS_initCfg[1]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[2],
         &FATFS_initCfg[2]
    },

    {NULL, NULL, NULL},

    {NULL, NULL, NULL}
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
Int32 BspUtils_initFileio(void *hEdma)
{
    Int32 retVal = BSP_SOK;
    FATFS_Error  fatFsStatus;

    if (gSdFileSysObj.sdInitDone == FALSE)
    {
        /* MMCSD FATFS initialization */
        FATFS_init();

        fatFsStatus = FATFS_open(0U, NULL, &gSdFileSysObj.fatfsHandle);

        if (fatFsStatus != FATFS_OK)
        {
            retVal = BSP_EFAIL;
        }

#if !defined(BARE_METAL)
        if (hEdma == NULL)
        {
            retVal = BSP_EFAIL;
        }
#endif
        if (retVal == BSP_SOK)
        {
            BspUtils_memset((Ptr) & gSdFileSysObj, 0, sizeof (gSdFileSysObj));
#if !defined(BARE_METAL)
            gSdFileSysObj.hEdma    = (EDMA3_DRV_Handle) hEdma;
#endif
            gSdFileSysObj.edmaDone = BspOsal_semCreate((Int32) 0,
                                                       (Bool) TRUE);
            gSdFileSysObj.sdCardNotPresent = FALSE;
        }
        gSdFileSysObj.sdInitDone = TRUE;
    }
    return retVal;
}

Int32 BspUtils_deinitFileio(void)
{
    FATFS_Error  fatFsStatus;
    Int32        retVal = BSP_SOK;

    if (gSdFileSysObj.sdInitDone == TRUE)
    {
        BspOsal_semDelete(&gSdFileSysObj.edmaDone);
        gSdFileSysObj.sdInitDone = FALSE;
        BspUtils_memset((Ptr) & gSdFileSysObj, 0, sizeof (gSdFileSysObj));

        /* Close FATFS */
        fatFsStatus = FATFS_close(gSdFileSysObj.fatfsHandle);
        if (fatFsStatus != FATFS_OK)
        {
            retVal = BSP_EFAIL;
        }
    }
    return (retVal);
}

Int32 BspUtils_appLoadFileFromSd(const Char *fileName,
                                 const Char *dirName,
                                 void       *bufAddr,
                                 UInt32      bufSize,
                                 UInt32     *bytesRead)
{
    FIL     fp;
    FRESULT fresult = FR_OK;
    Int32   retVal  = BSP_SOK;
    UInt32  startTime, endTime;
    Char    completeName[512];

    if ((gSdFileSysObj.sdInitDone != TRUE) ||
        (gSdFileSysObj.sdCardNotPresent == TRUE))
    {
        fresult = FR_NOT_READY;
    }

    strcpy(completeName, "0:");
    strncat(completeName, dirName, 128);
    strcat(completeName, "/");
    strncat(completeName, fileName,128);

    if (fresult == FR_OK)
    {
        fresult = f_open(&fp, completeName, (BYTE) FA_READ);
        if (fresult != FR_OK)
        {
            GT_0trace(BspAppTrace, GT_DEBUG,
                      "File open error \r\n");
        }
        else
        {
            GT_1trace(BspAppTrace, GT_INFO,
                      "Loading File %s from SD Card...\r\n", fileName);
            startTime = BspOsal_getCurTimeInMsec();
            fresult   = f_read(&fp, bufAddr, bufSize, bytesRead);
            endTime   = BspOsal_getCurTimeInMsec();
            if (fresult != FR_OK)
            {
                GT_0trace(BspAppTrace, GT_DEBUG, "\r\n File read failed \r\n");
            }
            f_close(&fp);
            GT_2trace(BspAppTrace, GT_INFO,
                      "File Size: %d bytes, Time Taken: %d ms!!\r\n",
                      *bytesRead, (endTime - startTime));
        }
    }

    if (fresult == FR_OK)
    {
        retVal = BSP_SOK;
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return retVal;
}

Int32 BspUtils_appSaveFileToSd(const Char *fileName,
                               const Char *dirName,
                               const void *bufAddr,
                               UInt32      bufSize,
                               UInt32     *bytesWritten)
{
    /* Note that save to Memory card is not successful due to below JIRA
     * Ref: JIRA ID: PRSDK-3520
     * The write returns DISK ERROR and hence this fails 
     */
    FIL     fp;
    FRESULT fresult = FR_OK;
    Int32   retVal  = BSP_SOK;
    UInt32  startTime, endTime;
    DIR     dirObj;

    if ((gSdFileSysObj.sdInitDone != TRUE) ||
        (gSdFileSysObj.sdCardNotPresent == TRUE))
    {
        fresult = FR_NOT_READY;
    }


    if (fresult == FR_OK)
    {
        if (dirName != NULL)
        {
            fresult   = f_opendir(&dirObj, dirName);

            if ((fresult == FR_NOT_READY) || (fresult == FR_DISK_ERR))
            {
                gSdFileSysObj.sdCardNotPresent = TRUE;
            }
            else
            {
                if (fresult == FR_NO_PATH)
                {
                    fresult = f_mkdir(dirName);
                    if (fresult == FR_OK)
                    {
                          fresult = f_opendir(&dirObj, dirName);
                    }
                }
                if (fresult != FR_OK)
                {
                    GT_1trace(BspAppTrace, GT_INFO,
                              "FatFs: CD to dir %s failed \r\n", dirName);
                }
            }
        }
        else
        {
            /* Dir name is NULL. Change dir to root dir */
            fresult   = f_opendir (&dirObj, "/");
            if (fresult != FR_OK)
            {
                if ((fresult == FR_NOT_READY) || (fresult == FR_DISK_ERR))
                {
                    gSdFileSysObj.sdCardNotPresent = TRUE;
                }
                else
                {
                    GT_0trace(BspAppTrace, GT_INFO,
                              "FatFs: CD to root dir failed \r\n");
                }
            }
        }
    }

    if (fresult == FR_OK)
    {
        fresult = f_open(&fp, fileName, (BYTE) FA_WRITE);
    }
    if (fresult == FR_OK)
    {
        f_close(&fp);
        GT_0trace(BspAppTrace, GT_DEBUG,
                  "File already exists on SD card. Delete it.\r\n");
        fresult = f_unlink(fileName);
        if (fresult != FR_OK)
        {
            GT_0trace(BspAppTrace, GT_DEBUG, "\r\n File delete failed \r\n");
        }
    }
    if ((fresult == FR_OK) || (fresult == FR_NO_FILE))
    {
        fresult = f_open(&fp, fileName, (BYTE) FA_CREATE_NEW);
        if (fresult != FR_OK)
        {
            GT_0trace(BspAppTrace, GT_DEBUG, "\r\n File create failed \r\n");
        }
        else
        {
            f_close(&fp);
            /*Open handle to the newly created file*/
            fresult = f_open(&fp, fileName, (BYTE) FA_WRITE);
        }
    }
    if (fresult == FR_OK)
    {
        GT_2trace(BspAppTrace, GT_INFO,
                  "Saving buffer at address 0x%.8x to file %s in Sd Card \r\n",
                  bufAddr, fileName);
        startTime = BspOsal_getCurTimeInMsec();
        fresult   = f_write(&fp, bufAddr, bufSize, bytesWritten);

        endTime   = BspOsal_getCurTimeInMsec();
        if (fresult != FR_OK)
        {
            GT_0trace(BspAppTrace, GT_DEBUG, "\r\n File write failed \r\n");
        }
        else
        {
            GT_2trace(BspAppTrace, GT_INFO,
                  "File Size %d, Time taken to write is %d ms \r\n",
                  *bytesWritten, (endTime - startTime));
        }
        f_close(&fp);
    }

    if (fresult == FR_OK)
    {
        retVal = BSP_SOK;
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return retVal;
}
/* Nothing past this point */
